#ifndef __WORLD_H_CLASS__
#define __WORLD_H_CLASS__


class Cell;
class Food;

#include <vector>;
#include "game/cell.h";
#include "game/food.h";


class World {
    public:
    inline float GetCurrentTime() {return this->currentTime;};
    void Step(float delta);

    void DestroyCell(Cell* cell);

    protected:
    float width, height;
    std::vector<Cell*> cells;
    std::vector<Food*> food;

    float currentTime = 0;
};

World* g_World;


#endif
