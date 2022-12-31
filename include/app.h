#ifndef APP_HPP
#define APP_HPP

#include <chrono>
#include <piksel/baseapp.hpp>
#include "objects/world.h"

class App : public piksel::BaseApp {
public:
    App(World* w, int width, int height);
    void setup();
    void draw(piksel::Graphics& g);

protected:
    World* world;
    std::chrono::high_resolution_clock::time_point lastUpdateTime;
};
#endif /* APP_HPP */
