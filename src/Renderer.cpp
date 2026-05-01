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
    vertexCount(0),
    pvao(0),
    pvbo(0) {
}

Renderer::~Renderer() {
    // shutdown();
}

bool Renderer::init() {
    const char* vertexSource = R"(
    #version 330 core

    layout (location = 0) in vec3 aPosition;
    uniform mat4 uView;
    uniform mat4 uProjection;

    void main() {
        gl_Position = uProjection * uView * vec4(aPosition, 1.0);
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
    const float spacing = 20.0f / lineCount;

    for (int i = 0; i <= lineCount; i++) {
        float value = -10.0f + i * spacing;

        // vertical line
        gridVertices.push_back(value); // x
        gridVertices.push_back(0.0f); // y
        gridVertices.push_back(-10.0f); // z

        gridVertices.push_back(value);
        gridVertices.push_back(0.0f);
        gridVertices.push_back(10.0f);

        // horizontal line
        gridVertices.push_back(-10.0f); // x 
        gridVertices.push_back(0.0f); // y
        gridVertices.push_back(value); // z

        gridVertices.push_back(10.0f);
        gridVertices.push_back(0.0f);
        gridVertices.push_back(value);
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

    const char* pvertexSource = R"(
    #version 330 core

    layout (location = 0) in vec3 aPosition;
    uniform mat4 uView;
    uniform mat4 uProjection;

    void main() {
        gl_Position = uProjection * uView * vec4(aPosition, 1.0);
        gl_PointSize = 100.0 / gl_Position.w;
    }
    )";
    const char* pfragmentSource = R"(
    #version 330 core

    out vec4 FragColor;

    void main() {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    )";

    if (!particleShader.create(pvertexSource, pfragmentSource)) {
        return false;
    }

    glGenVertexArrays(1, &pvao);
    glGenBuffers(1, &pvbo);

    glBindVertexArray(pvao);
    glBindBuffer(GL_ARRAY_BUFFER, pvbo);

    glBufferData(GL_ARRAY_BUFFER, 1000 * 3 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    const char* qvertexSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPosition;

    out vec2 vUV;

    void main() {
        vUV = aPosition * 0.5 + 0.5;
        gl_Position = vec4(aPosition, 0.0, 1.0);
    }
    )";
    const char* qfragmentSource = R"(
    #version 330 core

    in vec2 vUV;
    out vec4 FragColor;

    uniform vec3 uCameraPos;
    uniform vec3 uCameraFront;
    uniform vec3 uCameraRight;
    uniform vec3 uCameraUp;

    void main() {
        vec2 uv = vUV * 2.0 - 1.0;

        FragColor = vec4(abs(uv.x), abs(uv.y), 0.0, 1.0);
    }
    )";

    if (!qShader.create(qvertexSource, qfragmentSource)) {
        return false;
    }

    float quadVertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f,  1.0f,
        -1.0f, -1.0f,
        1.0f,  1.0f,
        -1.0f,  1.0f
    };

    glGenVertexArrays(1, &qvao);
    glGenBuffers(1, &qvbo);

    glBindVertexArray(qvao);
    glBindBuffer(GL_ARRAY_BUFFER, qvbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

void Renderer::clear() {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    shader.setMat4("uView", camera.getViewMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix());
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

void Renderer::draw(const std::vector<Particle>& particles) {

    std::vector<float> particleVertices;

    for (const auto& p : particles) {
        particleVertices.push_back(p.position.x);
        particleVertices.push_back(p.position.y);
        particleVertices.push_back(p.position.z);
    }

    glBindVertexArray(pvao);
    glBindBuffer(GL_ARRAY_BUFFER, pvbo);

    glBufferSubData(GL_ARRAY_BUFFER, 0,
                particleVertices.size() * sizeof(float), 
                particleVertices.data());
    particleShader.use();
    particleShader.setMat4("uView", camera.getViewMatrix());
    particleShader.setMat4("uProjection", camera.getProjectionMatrix());
    glDrawArrays(GL_POINTS, 0, particles.size());
    glBindVertexArray(0);
}

void Renderer::drawRaymarch() {
    qShader.use();
    qShader.setVec3("uCameraPos", camera.position);
    qShader.setVec3("uCameraFront", camera.front);
    qShader.setVec3("uCameraRight", camera.side);
    qShader.setVec3("uCameraUp", camera.up);
    glBindVertexArray(qvao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}