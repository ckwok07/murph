#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
    : position(0.0f, 0.5f, 3.0f),
    yaw(-90.0f),
    pitch(0.0f),
    fov(45.0f),
    aspect(1.0f),
    front(0.0f, 0.0f, -1.0f) {
        updateVectors();
}

void Camera::updateVectors() {
    float x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    float y = sin(glm::radians(pitch));
    float z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::vec3(x,y,z);
    front = glm::normalize(front);
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
}
