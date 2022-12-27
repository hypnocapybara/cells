#include <algorithm>
#include "game/food.h"
#include "utils/geometry.h"


Food::Food(World* world, Point2 pos, int maxAmount, float radius, int maxCellsCount) : Entity(world, pos) {
    this->currentAmount = this->maxAmount = maxAmount;
    this->radius = radius;
    this->maxCellsCount = maxCellsCount;
}


void Food::Process() {
    // destroy if fully eaten
    if (this->currentAmount <= 0) {
        return this->Die();
    }
}

void Food::Die() {
    this->world->DestroyFood(this);
}

bool Food::IsCellInActiveZone(Cell* cell) {
    float distance = Point2::DistanceBetween(cell->GetPosition(), this->position);
    return distance <= this->radius;
}

bool Food::HasAvailableAmount() {
    return this->currentAmount > 0;
}

void Food::HandleEaten() {
    this->currentAmount--;
}

void Food::CellLeave(Cell* cell) {
    auto it = std::find(this->cells.begin(), this->cells.end(), cell);
    if(it != this->cells.end()) {
        this->cells.erase(it);
    }
}

void Food::CellOccupy(Cell* cell) {
    this->cells.push_back(cell);
}
