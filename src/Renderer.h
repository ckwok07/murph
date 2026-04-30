#pragma once
#include "Shader.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init();
    void clear();
    void shutdown();

private:
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float a = 1.0f;
    Shader shader;
    unsigned int vbo; // vertex buffer object
    unsigned int vao; // vertex array object
    int vertexCount;
};