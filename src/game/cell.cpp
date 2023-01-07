#include <string>
#include "game/cell.h"
#include "objects/world.h"
#include "utils/geometry.h"
#include "utils/generic.h"


Cell::Cell(World* world, Point2 pos, int ownerId, std::map<std::string, std::string> params) : Entity(world, pos) {
    this->userId = ownerId;

    this->healthCurrent = this->healthMax = std::stof(params["healthMax"]);
    this->lifetime = std::stof(params["lifetime"]);
    this->speed = std::stof(params["speed"]);
    this->radius = std::stof(params["radius"]);
    this->poiRadius = 0.0f;
    this->intention = Cell::Intention::Nothing;

    this->feedCurrent = 0;
    this->feedMax = std::stof(params["feedMax"]);
    this->feedCooldown = std::stof(params["feedCooldown"]);
    this->feedInterval = std::stof(params["feedInterval"]);
    this->maxTimeWithoutFood = std::stof(params["maxTimeWithoutFood"]);
    this->foodDetectRadius = std::stof(params["foodDetectRadius"]);

    this->attackRange = std::stof(params["attackRange"]);
    this->attackPower = std::stof(params["attackPower"]);
    this->attackCooldown = std::stof(params["attackCooldown"]);
    this->enemiesDetectRadius = std::stof(params["enemiesDetectRadius"]);

    this->lastFeedTime = this->lastAttackTime = this->birthTime = this->world->GetCurrentTime();
}

void Cell::Process() {
    // Do NON-decision logic:
    // if recharge from attack - wait
    // if full - split
    // if not enough food - die
    // if too old - die
    // if left the cell area - free the space
    if (this->feedBase && !this->IsWithinFoodBase()) {
        this->LeaveFoodBase();
    }

    if (this->IsOutOfHealth() || this->IsTooHungry() || this->IsTooOld()) {
        return this->Die();
    }

    if (this->IsInCooldownFromAttack() || this->IsInCooldownFromFeed()) {
        this->inMove = false;
        return;
    }

    if (this->CanSplit()) {
        return this->Split();
    }
    
    this->FormDecission();
}

bool Cell::CanSplit() {
    return this->feedCurrent > 0 && this->feedCurrent >= this->feedMax;
}

bool Cell::IsTooOld() {
    return this->birthTime + this->lifetime < this->world->GetCurrentTime();
}

bool Cell::IsTooHungry() {
    return this->lastFeedTime + this->maxTimeWithoutFood < this->world->GetCurrentTime();
}

bool Cell::IsInCooldownFromAttack() {
    return this->lastAttackTime + this->attackCooldown > this->world->GetCurrentTime();
}

bool Cell::IsInCooldownFromFeed() {
    return this->lastFeedTime + this->feedCooldown > this->world->GetCurrentTime();
}

bool Cell::CanAttack(Cell* otherCell) {
    if (otherCell->userId == this->userId || this->IsInCooldownFromAttack()) {
        return false;
    }

    float distance = Point2::DistanceBetween(this->position, otherCell->position);
    return distance < this->attackRange + this->radius + otherCell->radius;
}

bool Cell::CanEat() {
    return this->IsWithinFoodBase() && !this->IsInCooldownFromAttack() &&
        this->feedBase->HasAvailableAmount() && 
        this->lastFeedTime + this->feedInterval < this->world->GetCurrentTime();
}

void Cell::Eat() {
    if (!this->feedBase) {
        return;
    }

    this->feedBase->HandleEaten();
    this->lastFeedTime = this->world->GetCurrentTime();
    this->feedCurrent++;
}

void Cell::Attack(Cell* otherCell) {
    this->lastAttackTime = this->world->GetCurrentTime();
    this->StopActivity();
    otherCell->TakeDamage(this->attackPower);
}

void Cell::TakeDamage(float amount) {
    this->healthCurrent -= amount;
}

bool Cell::IsWithinFoodBase() {
    return this->feedBase && this->feedBase->IsCellInActiveZone(this);
}

void Cell::OccupyFoodBase(Food* food) {
    if (food->HasFreeSpots() && food->IsCellInActiveZone(this)) {
        food->CellOccupy(this);
        this->feedBase = food;
    }
}

void Cell::LeaveFoodBase() {
    if (this->feedBase) {
        this->feedBase->CellLeave(this);
        this->feedBase = nullptr;
    }
}

void Cell::Die() {
    this->LeaveFoodBase();
    this->world->DestroyCell(this);
}

void Cell::Split() {
    Point2 newCell1Pos = this->position + Vector2(5, 0);
    Point2 newCell2Pos = this->position + Vector2(0, 5);

    this->world->CreateBacteria(newCell1Pos, this->userId);
    this->world->CreateBacteria(newCell2Pos, this->userId);
    this->Die();
}

void Cell::FormDecission() {
    if (this->HasReachedThePoi()) {
        // reached the point
        this->StopActivity();
        return;
    }

    // DETECT OTHER FOOD IF HUNGRY

    bool canEat = this->CanEat();
    bool isHungry = this->lastFeedTime + this->maxTimeWithoutFood / 2.0f < this->world->GetCurrentTime();
    if (
        (canEat && this->intention != Cell::Intention::WannaAttack) ||
        (canEat && isHungry)) {
        this->Eat();
        this->StopActivity();
        return;
    }

    if (isHungry && !this->IsWithinFoodBase()) {
        // trying to find the other food base
        float closestDistance = 999999999.0f;
        Food* closestFood = NULL;
        for (auto food : this->world->GetFood()) {
            if (!food->HasFreeSpots()) {
                continue;
            }

            float distance = Point2::DistanceBetween(food->GetPosition(), this->position);
            if (distance < closestDistance) {
                closestDistance = distance;
                closestFood = food;
            }
        }

        if (closestFood && closestDistance < this->foodDetectRadius) {
            this->intention = Cell::Intention::WannaFeed;
            this->MoveToPoint(closestFood->GetPosition(), closestFood->GetRadius() / 1.5f);
            return;
        }
    }

    // ATTACK
    float closestEnemyDistance = 999999999.0f;
    Cell* closestEnemy = NULL;
    for (auto cell : this->world->GetCells()) {
        if (cell->userId == this->userId) {
            continue;
        }

        float distance = Point2::DistanceBetween(cell->position, this->position);
        if (distance < closestEnemyDistance) {
            closestEnemyDistance = distance;
            closestEnemy = cell;
        }

        if (closestEnemy && closestEnemyDistance < this->enemiesDetectRadius) {
            if (this->CanAttack(closestEnemy)) {
                this->Attack(closestEnemy);
            } else {
                this->intention = Cell::Intention::WannaAttack;
                this->MoveToPoint(
                    closestEnemy->position,
                    this->radius + closestEnemy->radius + this->attackRange
                );
            }
        }
    }

    if (this->feedBase && this->intention == Cell::Intention::Nothing) {
        this->intention = Cell::Intention::Patrolling;
        Point2 poi = Point2::RandomPointWithinRadius(
            this->feedBase->GetPosition(),
            this->feedBase->GetRadius() / 1.5f
        );
        this->MoveToPoint(poi, this->radius * 1.2f);
    }
}

bool Cell::HasReachedThePoi() {
    return this->poiRadius > EPSILON && Point2::DistanceBetween(this->position, this->poi) < this->poiRadius;
}

void Cell::MoveToPoint(Point2 poi, float poiRadius) {
    this->poi = poi;
    this->inMove = true;
    this->poiRadius = poiRadius;
}

void Cell::StopActivity() {
    this->inMove = false;
    this->poiRadius = 0.0f;
    this->intention = Cell::Intention::Nothing;
}
