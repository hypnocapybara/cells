#ifndef __ENTITY_H_CLASS__
#define __ENTITY_H_CLASS__

class Point2;

#include "utils/geometry.h"
#include "objects/world.h"

enum EntityType {
    unknown,
    food,
    cell
};

class Entity {
    public:
    Entity(World* world, Point2 pos) {
        this->position = pos;
        this->world = world;
    };
    virtual void Process() = 0;
    virtual EntityType GetType() {
        return EntityType::unknown;
    };

    inline Point2 GetPosition() {return this->position;}

    protected:
    Point2 position;
    World* world;

    friend class World;
};

#endif
