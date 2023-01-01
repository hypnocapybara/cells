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

    for (auto food : this->food) {
        int freeSpots = food->GetMaxCellsCount() - food->GetCurrentCellsCount();
        if (freeSpots <= 0) {
            continue;
        }

        for (auto cell : this->cells) {
            if (freeSpots <= 0 || cell->feedBase) {
                break;
            }

            if (food->IsCellInActiveZone(cell)) {
                cell->OccupyFoodBase(food);
                freeSpots--;
            }
        }
    }

    for (int i = 0; i < this->food.size();) {
        Food* food = this->food[i];
        int sizeBefore = this->food.size();
        food->Process();
        if (sizeBefore == this->food.size())
            i++;
    }

    for (int i = 0; i < this->cells.size();) {
        Cell* cell = this->cells[i];
        int sizeBefore = this->cells.size();
        cell->Process();
        if (sizeBefore == this->cells.size())
            i++;
    }

    for (auto cell : this->cells) {
        if (cell->inMove) {
            float distanceToPOI = Point2::DistanceBetween(cell->position, cell->poi);
            float distanceInStep = delta * cell->speed;
            if (distanceInStep >= distanceToPOI) {
                cell->position = cell->poi;
            } else {
                Vector2 direction = Vector2::FromPoints(cell->position, cell->poi);
                direction.Normalize();
                direction.MultiplyLength(distanceInStep);

                cell->position += direction;
            }
        }
    }
}

Cell* World::CreateBacteria(Point2 position, int ownerId) {
    std::map<std::string, std::string> params{
        {"healthMax", "100"},
        {"lifetime", "100"},
        {"speed", "50"},
        {"feedMax", "5"},
        {"feedCooldown", "1"},
        {"feedInterval", "3"},
        {"maxTimeWithoutFood", "20"},
        {"foodDetectRadius", "600"},
        {"attackRange", "50"},
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
    for (auto cell : food->cells) {
        cell->LeaveFoodBase();
    }

    auto it = std::find(this->food.begin(), this->food.end(), food);
    assert(it != this->food.end());
    this->food.erase(it);

    delete food;
}
