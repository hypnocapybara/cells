#include "food.h"
#include "utils/geometry.h"


void Food::Process() {
    // destroy if fully eaten
}

bool Food::IsCellInActiveZone(Cell* cell) {
    float distance = Point2::DistanceBetween(cell->GetPosition(), this->position);
    return distance <= this->radius;
}
