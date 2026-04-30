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
    return true;
}

void Renderer::clear() {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::shutdown() {

}