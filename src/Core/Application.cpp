#include "Application.hpp"

Application::Application() 
    : m_window(1280, 720, "Liotru Engine v0.1"), m_running(true) {}

void Application::run() {
    while (m_running && !m_window.shouldClose()) {
        m_window.clear(0.1f, 0.1f, 0.15f); // Un grigio scuro moderno
        
        // Qui andrà tutta la logica di rendering futuro
        
        m_window.update();
    }
}