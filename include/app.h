#ifndef APP_HPP
#define APP_HPP

#include <chrono>
#include <piksel/baseapp.hpp>
#include "objects/world.h"
#include "utils/geometry.h"

#define KEY_UP 1 << 0
#define KEY_DOWN 1 << 1
#define KEY_LEFT 1 << 2
#define KEY_RIGHT 1 << 3

#define PIKSEL_KEY_UP 265
#define PIKSEL_KEY_DOWN 264
#define PIKSEL_KEY_LEFT 263
#define PIKSEL_KEY_RIGHT 262

class App : public piksel::BaseApp {
public:
    App(World* w, int width, int height);
    void setup();
    void draw(piksel::Graphics& g);
    void keyPressed(int keycode);
    void keyReleased(int keycode);
    void mousePressed(int code);
    void mouseMoved(int x, int y);

protected:
    void ProcessCamera(float step);
    bool IsSeenByCamera(const Point2& point);

    void DrawCells(piksel::Graphics& g);
    void DrawFood(piksel::Graphics& g);

    World* world;
    std::chrono::high_resolution_clock::time_point lastUpdateTime;
    Point2 cameraPos;
    int pressedKeys;
    int mouseX, mouseY;
};
#endif /* APP_HPP */
