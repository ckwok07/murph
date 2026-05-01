#include "Physics.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

void Physics::addParticle(Particle p) {
    particles.push_back(p);
}

void Physics::update(float dt) {

    for (int i = 0; i < particles.size(); i++) {
        glm::vec3 oldAcceleration = particles[i].acceleration;
        glm::vec3 newAcceleration(0.0f,0.0f,0.0f);
        for (int j = 0; j < particles.size(); j++) {
            if (i == j) continue;
            glm::vec3 direction = particles[j].position - particles[i].position;
            float distance = glm::length(direction) + 0.1f;

            // float g = 6.6743 * pow(10, -11);
            float g = 0.01;
            newAcceleration += g * (particles[j].mass / (distance * distance)) * glm::normalize(direction);
        }

        particles[i].position += particles[i].velocity * dt + 0.5f * particles[i].acceleration * (dt * dt);    
        particles[i].velocity += (oldAcceleration + newAcceleration) * 0.5f * dt;
        particles[i].acceleration = newAcceleration;
    }
}