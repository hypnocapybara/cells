#ifndef __WORLD_H_CLASS__
#define __WORLD_H_CLASS__


class Cell;
class Food;
class Point2;

#include <vector>
#include "game/cell.h"
#include "game/food.h"
#include "utils/geometry.h"


class World {
    public:
    World(float width, float height);
    inline float GetCurrentTime() {return this->currentTime;};
    void Step(float delta);

    Cell* CreateBacteria(Point2 position, int ownerId);
    Food* CreateFood(Point2 position, int maxAmount, float radius, int maxCellsCount);
    void DestroyCell(Cell* cell);
    void DestroyFood(Food* food);

    const std::vector<Cell*>& GetCells() {return this->cells;};
    const std::vector<Food*>& GetFood() {return this->food;};

    protected:
    float width, height;
    std::vector<Cell*> cells;
    std::vector<Food*> food;

    float currentTime = 0;
};


#endif
