#ifndef APP_HPP
#define APP_HPP

#include <piksel/baseapp.hpp>

class App : public piksel::BaseApp {
public:
    App() : piksel::BaseApp(640, 480) {}
    void setup();
    void draw(piksel::Graphics& g);
};
#endif /* APP_HPP */
