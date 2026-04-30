#define GLFW_INCLUDE_NONE
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

Renderer::Renderer()
    : r(0.2f),
    g(0.2f),
    b(0.2f),
    a(1.0f),
    vao(0),
    vbo(0),
    vertexCount(0) {
}

Renderer::~Renderer() {
    // shutdown();
}

bool Renderer::init() {
    const char* vertexSource = R"(
    #version 330 core

    layout (location = 0) in vec3 aPosition;

    void main() {
        gl_Position = vec4(aPosition, 1.0);
    }
    )";
    const char* fragmentSource = R"(
    #version 330 core

    out vec4 FragColor;

    void main() {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    )";

    if (!shader.create(vertexSource, fragmentSource)) {
        return false;
    }

    std::vector<float> gridVertices;

    const int lineCount = 20;
    const float spacing = 2.0f / lineCount;

    for (int i = 0; i <= lineCount; i++) {
        float value = -1.0f + i * spacing;

        // vertical line
        gridVertices.push_back(value);
        gridVertices.push_back(-1.0f);
        gridVertices.push_back(0.0f);

        gridVertices.push_back(value);
        gridVertices.push_back(1.0f);
        gridVertices.push_back(0.0f);

        // horizontal line
        gridVertices.push_back(-1.0f);
        gridVertices.push_back(value);
        gridVertices.push_back(0.0f);

        gridVertices.push_back(1.0f);
        gridVertices.push_back(value);
        gridVertices.push_back(0.0f);
    }

    vertexCount = static_cast<int>(gridVertices.size() / 3);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 
                gridVertices.size() * sizeof(float), 
                gridVertices.data(), 
                GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

void Renderer::clear() {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, vertexCount);
    glBindVertexArray(0);
}

void Renderer::shutdown() {
    if (vbo != 0) {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }

    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }
    shader.destroy();
}