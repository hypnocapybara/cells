#include "objects/world.h"
#include "app.h"


int main() {
    World* world = new World(1200, 1200);
    world->CreateBacteria(Point2(100, 100), 0);
    world->CreateFood(Point2(120, 120), 100, 100, 2);
    world->CreateFood(Point2(350, 350), 100, 100, 10);

    // for (int i = 0; i < 9999999; i++) {
    //     world->Step(0.022);
    // }

    App app(world, 800, 600);
    app.start();
    return 0;
}
