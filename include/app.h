#ifndef APP_HPP
#define APP_HPP

#include <chrono>
#include <piksel/baseapp.hpp>
#include "objects/world.h"
#include "utils/geometry.h"

class App : public piksel::BaseApp {
public:
    App(World* w, int width, int height);
    void setup();
    void draw(piksel::Graphics& g);
    void keyPressed(int keycode);

protected:
    World* world;
    std::chrono::high_resolution_clock::time_point lastUpdateTime;
    Point2 cameraPos;
};
#endif /* APP_HPP */
