#include "food.h"
#include "utils/geometry.h"


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
