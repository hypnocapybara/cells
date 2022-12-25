#ifndef __ENTITY_H_CLASS__
#define __ENTITY_H_CLASS__

class Point2;
class Vector2;

#include "utils/geometry.h";

enum EntityType {
    unknown,
    food,
    cell
};

class Entity {
    public:
    Entity(Point2 pos) {this->position = pos;};
    virtual void Process() = 0;
    virtual EntityType GetType() {
        return EntityType::unknown;
    };

    inline Point2 GetPosition() {return this->position;}

    protected:
    Point2 position;
};

#endif
