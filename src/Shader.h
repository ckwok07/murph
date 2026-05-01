#pragma once
#include <glm/glm.hpp>

class Shader {
public:
    Shader();
    ~Shader();

    bool create(const char* vertexSource, const char* fragmentSource);
    void use() const;
    void destroy();
    void Shader::setMat4(const char* name, const glm::mat4& value) const;

private:
    unsigned int programId;
};