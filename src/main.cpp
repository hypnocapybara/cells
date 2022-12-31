#include "objects/world.h"
#include "app.h"


int main() {
    World* world = new World();
    world->CreateBacteria(Point2(100, 100), 0);
    world->CreateFood(Point2(120, 120), 10, 100, 2);

    App app(world, 800, 600);
    app.start();
    return 0;
}
