#include "Shader.h"
#include <glad/glad.h>

Shader::Shader()
    : programId(0) {
}

Shader::~Shader() {
    destroy();
}

bool Shader::create(const char* vertexSource, const char* fragmentSource) {
    // compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    
    programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);


    glLinkProgram(programId);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programId != 0;
}

void Shader::use() const {
    glUseProgram(programId);
}

void Shader::destroy() {
    if (programId != 0) {
        glDeleteProgram(programId);
        programId = 0;
    }
}

void Shader::setMat4(const char* name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(programId, name), 1, GL_FALSE, &value[0][0]);
}