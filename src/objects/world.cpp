#include <map>
#include <string>
#include <algorithm>
#include <cassert>
#include "objects/world.h"


void World::Step(float delta) {
    // occupy the base for free cells
    // process all entities
    // move entities
    this->currentTime += delta;

    for (auto it = this->food.begin(); it != this->food.end(); it++) {
        Food* food = *it;
        int freeSpots = food->GetMaxCellsCount() - food->GetCurrentCellsCount();
        if (freeSpots <= 0) {
            continue;
        }

        for (auto gt = this->cells.begin(); gt != this->cells.end(); gt++) {
            if (freeSpots <= 0) {
                break;
            }

            Cell* cell = *gt;
            if (cell->feedBase) {
                continue;
            }

            if (food->IsCellInActiveZone(cell)) {
                cell->OccupyFoodBase(food);
                freeSpots--;
            }
        }
    }

    for (auto it = this->food.begin(); it != this->food.end(); it++) {
        Food* food = *it;
        food->Process();
    }

    for (auto it = this->cells.begin(); it != this->cells.end(); it++) {
        Cell* cell = *it;
        cell->Process();
    }

    for (auto it = this->cells.begin(); it != this->cells.end(); it++) {
        Cell* cell = *it;
        if (cell->wannaMove) {
            float distanceToPOI = Point2::DistanceBetween(cell->position, cell->poi);
            float distanceInStep = delta * cell->speed;
            if (distanceInStep >= distanceToPOI) {
                cell->position = cell->poi;
            } else {
                Vector2 direction = Vector2::FromPoints(cell->position, cell->poi);
                direction.Normalize();
                direction.MultiplyLength(distanceInStep);

                cell->position.AddVector(direction);
            }
        }
    }
}

Cell* World::CreateBacteria(Point2 position, int ownerId) {
    std::map<std::string, std::string> params{
        {"healthMax", "100"},
        {"lifetime", "100"},
        {"speed", "100"},
        {"feedMax", "5"},
        {"feedCooldown", "2"},
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
    for (auto it = food->cells.begin(); it != food->cells.end(); it++) {
        (*it)->LeaveFoodBase();
    }

    auto it = std::find(this->food.begin(), this->food.end(), food);
    assert(it != this->food.end());
    this->food.erase(it);

    delete food;
}
