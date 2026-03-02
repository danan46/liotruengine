#include "Renderer.hpp"
#include <iostream>

void Renderer::init() {
    m_defaultShader = new Shader("shaders/default.vert", "shaders/default.frag");

    // Definiamo un triangolo (Dati grezzi)
    Vertex vertices[] = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // Rosso
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // Verde
        {{ 0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}  // Blu
    };

    // HPA: Generiamo i buffer sulla GPU e inviamo i dati in un colpo solo
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Diciamo alla GPU come leggere la struttura "Vertex"
    // Posizione (Location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // Colore (Location 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Renderer::beginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawTriangle() {
    m_defaultShader->use();
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::shutdown() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}
