#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Particle.h"

class Renderer {
public:
    Renderer();
    ~Renderer();
    Camera camera;
    bool init();
    void clear();
    void shutdown();

    void draw(const std::vector<Particle>& particles);

private:
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float a = 1.0f;
    Shader shader;
    Shader particleShader;
    unsigned int vbo; // vertex buffer object
    unsigned int vao; // vertex array object
    int vertexCount;

    unsigned int pvbo;
    unsigned int pvao;
};