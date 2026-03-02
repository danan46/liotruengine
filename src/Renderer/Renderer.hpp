#pragma once
#include <glad/glad.h>
#include <vector>
#include "Shader.hpp"

// Una struttura semplice per i dati dei vertici (HPA: Dati contigui in memoria)
struct Vertex {
    float position[3];
    float color[3];
};

class Renderer {
public:
    void init();
    void shutdown();

    // Pulizia del frame
    void beginFrame();
    void endFrame();

    // Funzione di disegno (per ora di test)
    void drawTriangle();

private:
    unsigned int m_VAO = 0, m_VBO = 0; // Identificativi per la memoria GPU
    Shader* m_defaultShader = nullptr; // Shader di default per il rendering
};
