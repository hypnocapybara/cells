#ifndef __FOOD_H_CLASS__
#define __FOOD_H_CLASS__


class Point2;
class Entity;
class Cell;
class World;


#include <vector>
#include "utils/geometry.h"
#include "entity.h"
#include "cell.h"
#include "objects/world.h"

class Food : public Entity {
    public:
    Food(World* world, Point2 pos, int maxAmount, float radius, int maxCellsCount) : Entity(world, pos) {
        this->currentAmount = this->maxAmount = maxAmount;
        this->radius = radius;
        this->maxCellsCount = maxCellsCount;
    }

    EntityType GetType() {
        return EntityType::food;
    }

    void Process();
    void Die();

    inline int GetMaxCellsCount() {return this->maxCellsCount;}
    inline int GetCurrentCellsCount() {return this->cells.size();}
    inline bool HasFreeSpots() {return this->GetCurrentCellsCount() < this->GetMaxCellsCount();}
    inline bool HasAmountAvailable() {return this->currentAmount > 0;}

    bool IsCellInActiveZone(Cell* cell);
    void HandleEaten();
    void CellLeave(Cell* cell);
    void CellOccupy(Cell* cell);

    protected:
    int currentAmount = 0;
    int maxAmount = 0;
    std::vector<Cell*> cells;
    int maxCellsCount = 0;
    float radius = 0;

    friend class World;
};

#endif
