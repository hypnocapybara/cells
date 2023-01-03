#include "objects/world.h"
#include "app.h"


int main() {
    World* world = new World(2000, 2000);

    world->CreateBacteria(Point2(110, 100), 0);
    world->CreateBacteria(Point2(100, 100), 0);
    world->CreateBacteria(Point2(100, 110), 0);
    world->CreateFood(Point2(120, 120), 100, 100, 10);
    world->CreateFood(Point2(130, 120), 100, 100, 10);
    world->CreateFood(Point2(120, 130), 100, 100, 10);

    world->CreateBacteria(Point2(1000, 1000), 1);
    world->CreateBacteria(Point2(1010, 1000), 1);
    world->CreateBacteria(Point2(1000, 1010), 1);
    world->CreateFood(Point2(1010, 1010), 100, 100, 10);
    world->CreateFood(Point2(900, 950), 100, 100, 10);
    world->CreateFood(Point2(1000, 950), 100, 100, 10);

    world->CreateFood(Point2(300, 300), 100, 100, 10);
    world->CreateFood(Point2(320, 320), 100, 100, 10);

    world->CreateFood(Point2(600, 600), 100, 100, 10);
    world->CreateFood(Point2(580, 620), 100, 100, 10);

    // for (int i = 0; i < 9999999; i++) {
    //     world->Step(0.09);
    // }

    App app(world, 1000, 800);
    app.start();
    return 0;
}
