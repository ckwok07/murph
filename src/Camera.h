#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    Camera();
    glm::vec3 position;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::vec3 front;
    glm::vec3 side;
    glm::vec3 up;
    void mouseEvent(float dx, float dy);
    void keyEvent(bool w, bool a, bool s, bool d, bool shift, bool space, float dt);

private:
    float yaw;
    float pitch;
    float fov;
    float aspect;
    void updateVectors();
};