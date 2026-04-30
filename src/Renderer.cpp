#define GLFW_INCLUDE_NONE
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Renderer::Renderer()
    : r(1.0f),
    g(1.0f),
    b(1.0f),
    a(1.0f) {

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
    return shader.create(vertexSource, fragmentSource);
}

void Renderer::clear() {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::shutdown() {
    shader.destroy();
}