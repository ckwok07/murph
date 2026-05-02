#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Camera::Camera()
    : position(0.0f, 1.0f, 30.0f),
    yaw(-90.0f),
    pitch(0.0f),
    fov(45.0f),
    aspect(1.0f),
    front(0.0f, 0.0f, -1.0f),
    side(1.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f) {
        updateVectors();
}

void Camera::updateVectors() {
    float x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    float y = sin(glm::radians(pitch));
    float z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::vec3(x,y,z);
    front = glm::normalize(front);

    side = glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f));
    side = glm::normalize(side);
    up = glm::normalize(glm::cross(side, front));
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
}

void Camera::mouseEvent(float dx, float dy) {
    yaw += dx;
    pitch += dy;
    pitch = std::clamp(pitch, -89.0f, 89.0f);
    updateVectors();
}

void Camera::keyEvent(bool w, bool a, bool s, bool d, bool shift, bool space, float dt) {
    if (w) position += front * 5.0f * dt;
    if (s) position -= front * 5.0f * dt;
    if (d) position += side * 5.0f * dt;
    if (a) position -= side * 5.0f * dt;
    if (space) position += glm::vec3(0.0f, 1.0f, 0.0f) * 5.0f * dt;
    if (shift) position -= glm::vec3(0.0f, 1.0f, 0.0f) * 5.0f * dt;
}

