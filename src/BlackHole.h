#pragma once
#include <glm/glm.hpp>

struct BlackHole {
    glm::vec3 position;
    float mass;
    float eventHorizonRadius;
    float diskInnerRadius;
    float diskOuterRadius;

    float schwarzschildRadius() const {
        const float G = 1.0f;
        const float c = 1.0f;
        return 2.0f * G * mass / (c * c);
    }
};