#pragma once
#include "Window.hpp"

class Application {
public:
    Application();
    void run();

private:
    Window m_window;
    bool m_running;
};