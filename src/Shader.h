#pragma once
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader();
    ~Shader();

    bool create(const char* vertexSource, const char* fragmentSource);
    void use() const;
    void destroy();
    void setMat4(const char* name, const glm::mat4& value) const;

    void setVec3(const char* name, const glm::vec3& value) const;

    void setFloat(const char* name, float value) const;

private:
    unsigned int programId;
};