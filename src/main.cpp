#include "objects/world.h"
#include "app.h"


int main() {
    World* world = new World();
    world->CreateBacteria(Point2(100, 100), 0);
    world->CreateFood(Point2(120, 120), 10, 100, 2);

    for (int i = 0; i < 3000; i++) {
        world->Step(0.05);
    }

    App app;
    app.start();
    return 0;
}
