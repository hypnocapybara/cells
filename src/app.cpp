#include "app.h"

App::App(World* w, int width, int height) : piksel::BaseApp(width, height) {
    this->world = w;
    this->lastUpdateTime = std::chrono::system_clock::now();
}

void App::setup() {
    // load fonts and images here
}

void App::draw(piksel::Graphics& g) {
    auto curtime = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedSeconds = curtime - this->lastUpdateTime;
    float step = elapsedSeconds.count();
    if (step > 0.05) {
        this->world->Step(step);
        this->lastUpdateTime = curtime;
    }

    g.background(glm::vec4(0.05f, 0.05f, 0.05f, 1.0f));

    g.ellipseMode(piksel::DrawMode::CENTER);
    for (auto cell : this->world->GetCells()) {
        auto pos = cell->GetPosition();
        g.ellipse(pos.x, pos.y, 10, 10);
    }
}
