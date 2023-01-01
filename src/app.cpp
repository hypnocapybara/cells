#include "app.h"

App::App(World* w, int width, int height) : piksel::BaseApp(width, height) {
    this->world = w;
    this->lastUpdateTime = std::chrono::system_clock::now();
    this->cameraPos = Point2(0, 0);
    this->pressedKeys = 0;
}

void App::setup() {
    // load fonts and images here
}

void App::keyPressed(int keycode) {
    switch (keycode)
    {
    case PIKSEL_KEY_UP:
        this->pressedKeys |= KEY_UP;
        break;

    case PIKSEL_KEY_DOWN:
        this->pressedKeys |= KEY_DOWN;
        break;

    case PIKSEL_KEY_LEFT:
        this->pressedKeys |= KEY_LEFT;
        break;

    case PIKSEL_KEY_RIGHT:
        this->pressedKeys |= KEY_RIGHT;
        break;
    
    default:
        break;
    }
}

void App::keyReleased(int keycode) {
    switch (keycode)
    {
    case PIKSEL_KEY_UP:
        this->pressedKeys &= ~KEY_UP;
        break;

    case PIKSEL_KEY_DOWN:
        this->pressedKeys &= ~KEY_DOWN;
        break;

    case PIKSEL_KEY_LEFT:
        this->pressedKeys &= ~KEY_LEFT;
        break;

    case PIKSEL_KEY_RIGHT:
        this->pressedKeys &= ~KEY_RIGHT;
        break;
    
    default:
        break;
    }
}

void App::draw(piksel::Graphics& g) {
    auto curtime = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedSeconds = curtime - this->lastUpdateTime;
    float step = elapsedSeconds.count();
    if (step > 0.05) {
        this->world->Step(step);
        this->lastUpdateTime = curtime;
    }

    this->ProcessCamera(step);

    g.background(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    g.ellipseMode(piksel::DrawMode::CENTER);

    for (auto cell : this->world->GetCells()) {
        if (!this->IsSeenByCamera(cell->GetPosition())) {
            continue;
        }

        g.strokeWeight(1);
        Point2 pos = cell->GetPosition();
        pos.x -= this->cameraPos.x;
        pos.y -= this->cameraPos.y;

        g.fill(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
        g.ellipse(pos.x, pos.y, 10, 10);
    }

    g.rectMode(piksel::DrawMode::CENTER);
    for (auto food : this->world->GetFood()) {
        Point2 pos = food->GetPosition();
        pos.x -= this->cameraPos.x;
        pos.y -= this->cameraPos.y;

        g.rect(pos.x, pos.y, 10, 10);
    }
}

void App::ProcessCamera(float step) {
    const float cameraSpeed = 400.0f;
    if (this->pressedKeys == 0) {
        return;
    }

    Vector2 cameraDirection;
    if (this->pressedKeys & KEY_UP) {
        cameraDirection.y += -1;
    }

    if (this->pressedKeys & KEY_DOWN) {
        cameraDirection.y += 1;
    }

    if (this->pressedKeys & KEY_LEFT) {
        cameraDirection.x -= 1;
    }

    if (this->pressedKeys & KEY_RIGHT) {
        cameraDirection.x += 1;
    }

    cameraDirection.MultiplyLength(step * cameraSpeed);
    this->cameraPos += cameraDirection;
}

bool App::IsSeenByCamera(const Point2& point) {
    const int cameraDelta = 10;
    Point2 rectPos = Point2(this->cameraPos.x - cameraDelta, this->cameraPos.y - cameraDelta);
    return Point2::IsPointWithinRect(point, rectPos, this->width + cameraDelta, this->height + cameraDelta);
}
