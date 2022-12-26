#ifndef __CELL_H_CLASS__
#define __CELL_H_CLASS__

class Entity;
class Food;
class Point2;
class World;

#include <map>
#include <string>

#include "entity.h"
#include "food.h"
#include "utils/geometry.h"
#include "objects/world.h"

class Cell : public Entity {
    public:
    Cell(World* world, Point2 pos, int ownerId, std::map<std::string, std::string> params);

    EntityType GetType() {
        return EntityType::cell;
    };

    void Process();

    bool CanSplit();
    void Split();

    bool IsTooHungry();
    bool IsTooOld();
    inline bool IsOutOfHealth() {return this->healthCurrent < 0;};
    void Die();

    bool IsInCooldownFromAttack();
    bool CanAttack(Cell* otherCell);
    void Attack(Cell* otherCell);
    void TakeDamage(float amount);

    bool CanEat(Food* food);
    void Eat(Food* food);
    void OccupyFoodBase(Food* food);
    void LeaveFoodBase();
    bool IsWithinFoodBase();

    protected:
    // Variables for actions:
    // go to
    // Point2 target;
    // // attack
    // Cell* attackTarget = nullptr;
    // eat
    Food* feedBase = nullptr;

    // health
    float healthCurrent = 0;
    float healthMax = 0;
    float birthTime = 0;
    float lifetime = 0;

    // move
    Vector2 direction;
    float speed = 0;

    // feed & fission variables
    // when reach feedMax - self-dublicate
    int feedCurrent = 0, feedMax = 0;
    float lastFeedTime = 0; // last global time when cell feeded
    float feedCooldown = 0; // cooldown between feed actions
    float maxTimeWithoutFood = 0;
    float foodDetectRadius = 0;

    // attack variables
    float attackRange = 0;
    float attackPower = 0;
    float lastAttackTime = 0;
    float attackCooldown = 0;
    float enemiesDetectRadius = 0;

    // belonging
    int userId = 0;

};

 

#endif
