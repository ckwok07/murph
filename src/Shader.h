#pragma once

class Shader {
public:
    Shader();
    ~Shader();

    bool create(const char* vertexSource, const char* fragmentSource);
    void use() const;
    void destroy();

private:
    unsigned int programId;
};