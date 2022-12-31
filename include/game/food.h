#ifndef __FOOD_H_CLASS__
#define __FOOD_H_CLASS__


class Point2;
class Entity;
class Cell;
class World;
// enum EntityType;


#include <vector>

#include "utils/geometry.h"
#include "game/entity.h"
#include "game/cell.h"
#include "objects/world.h"

class Food : public Entity {
    public:
    Food(World* world, Point2 pos, int maxAmount, float radius, int maxCellsCount);

    // EntityType GetType() {
    //     return EntityType::food;
    // }

    void Process();
    void Die();

    inline float GetRadius() {return this->radius;}

    inline int GetMaxCellsCount() {return this->maxCellsCount;}
    inline int GetCurrentCellsCount() {return this->cells.size();}
    inline bool HasFreeSpots() {return this->GetCurrentCellsCount() < this->GetMaxCellsCount();}
    inline bool HasAmountAvailable() {return this->currentAmount > 0;}

    bool IsCellInActiveZone(Cell* cell);
    bool HasAvailableAmount();
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
