#include "objects/world.h"


int main() {
    World* world = new World();
    world->CreateBacteria(Point2(100, 100), 0);

    for (int i = 0; i < 100; i++) {
        world->Step(0.05);
    }

    return 0;
}

