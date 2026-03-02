#pragma once
#include "Window.hpp"
#include "Renderer/Renderer.hpp"

class Application {
    public:
        Application();
        void run();

    private:
        Window m_window;
        Renderer m_renderer;
        bool m_running;
};