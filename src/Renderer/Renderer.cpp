#include "Renderer.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

void Renderer::endFrame() {}

void Renderer::drawTriangle() {
    m_defaultShader->use();

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    // Inviamo la matrice allo shader
    unsigned int transformLoc = glGetUniformLocation(m_defaultShader->ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));    

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::shutdown() {
    if (m_defaultShader != nullptr) {
        delete m_defaultShader;
        m_defaultShader = nullptr;
    }

    if (m_VAO != 0) {
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;
    }
    if (m_VBO != 0) {
        glDeleteBuffers(1, &m_VBO);
        m_VBO = 0;
    }
}
