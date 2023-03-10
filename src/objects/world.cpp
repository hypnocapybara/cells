#include <map>
#include <string>
#include <algorithm>
#include <cassert>
#include "objects/world.h"


World::World(float width, float height) {
    this->width = width;
    this->height = height;
}

void World::Step(float delta) {
    // occupy the base for free cells
    // process all entities
    // move entities
    this->currentTime += delta;

    // Handle food bases occupied
    for (auto food : this->food) {
        int freeSpots = food->GetMaxCellsCount() - food->GetCurrentCellsCount();
        if (freeSpots <= 0) {
            continue;
        }

        for (auto cell : this->cells) {
            if (freeSpots <= 0 || cell->feedBase) {
                continue;
            }

            if (food->IsCellInActiveZone(cell)) {
                cell->OccupyFoodBase(food);
                freeSpots--;
            }
        }
    }

    // process food
    for (int i = 0; i < this->food.size();) {
        Food* food = this->food[i];
        int sizeBefore = this->food.size();
        food->Process();
        if (sizeBefore == this->food.size())
            i++;
    }

    // process cells
    for (int i = 0; i < this->cells.size();) {
        Cell* cell = this->cells[i];
        int sizeBefore = this->cells.size();
        cell->Process();
        if (sizeBefore == this->cells.size())
            i++;
    }

    // move cells: calculate velocities
    for (auto cell : this->cells) {
        cell->velocity = Vector2(0.0f, 0.0f);

        if (cell->inMove) {
            cell->velocity = Vector2::FromPoints(cell->position, cell->poi);
            cell->velocity.Normalize();
            cell->velocity *= cell->speed;
        }

        Vector2 collisionVelocity = Vector2(0.0f, 0.0f);

        for (auto otherCell : this->cells) {
            if (cell == otherCell) {
                continue;
            }

            if (cell->position == otherCell->position) {
                collisionVelocity = Vector2::RandomUnitVector() * cell->speed * 2;
                break;
            }

            float distanceBetweenCells = Point2::DistanceBetween(cell->position, otherCell->position);
            float collisionDistance = cell->radius * 1.1 + otherCell->radius * 1.1;

            if (distanceBetweenCells < collisionDistance) {
                float coefficient = 1 / (distanceBetweenCells / collisionDistance);
                Vector2 bouncingVector = Vector2::FromPoints(otherCell->position, cell->position);
                bouncingVector.Normalize();
                bouncingVector *= coefficient * cell->speed;
                collisionVelocity += bouncingVector;
            }
        }

        cell->velocity += collisionVelocity;
    }

    // move cells: change position
    for (auto cell : this->cells) {
        if (cell->velocity.IsZero()) {
            continue;
        }

        cell->position += cell->velocity * delta;

        // float distanceToPOI = Point2::DistanceBetween(cell->position, cell->poi);
        // float distanceInStep = delta * cell->speed;
        // if (distanceInStep >= distanceToPOI) {
        //     cell->position = cell->poi;
        // }
    }
}

Cell* World::CreateBacteria(Point2 position, int ownerId) {
    std::map<std::string, std::string> params{
        {"healthMax", "30"},
        {"lifetime", "100"},
        {"speed", "70"},
        {"radius", "5"},
        {"feedMax", "3"},
        {"feedCooldown", "1"},
        {"feedInterval", "3"},
        {"maxTimeWithoutFood", "20"},
        {"foodDetectRadius", "600"},
        {"attackRange", "4"},
        {"attackPower", "10"},
        {"attackCooldown", "1"},
        {"enemiesDetectRadius", "600"}
    };
    Cell* result = new Cell(this, position, ownerId, params);
    this->cells.push_back(result);
    return result;
}

Food* World::CreateFood(Point2 position, int maxAmount, float radius, int maxCellsCount) {
    Food* food = new Food(this, position, maxAmount, radius, maxCellsCount);
    this->food.push_back(food);
    return food;
}

void World::DestroyCell(Cell* cell) {
    cell->LeaveFoodBase();

    auto it = std::find(this->cells.begin(), this->cells.end(), cell);
    assert(it != this->cells.end());
    this->cells.erase(it);

    // TODO: create food?

    delete cell;
}

void World::DestroyFood(Food* food) {
    for (auto cell : this->cells) {
        if (cell->feedBase == food) {
            cell->LeaveFoodBase();
        }
    }

    for (auto& f : this->food) {
        if (f == food) {
            delete f;
            f = nullptr;
            break;
        }
    }

    this->food.erase(std::remove(this->food.begin(), this->food.end(), nullptr), this->food.end());
}
