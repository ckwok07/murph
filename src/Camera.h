#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    Camera();
    glm::vec3 position;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    float yaw;
    float pitch;
    float fov;
    float aspect;
    glm::vec3 front;
    void updateVectors();
};