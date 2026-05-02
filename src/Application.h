#pragma once

#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "Physics.h"
#include "BlackHole.h"

class Application {
public:
    Application();
    ~Application();

    int run();

private:
    bool init();
    void loop();
    void shutdown();

    void mouseEvent(float dx, float dy);

private:
    GLFWwindow* window;
    Renderer renderer;
    Physics physics;
    BlackHole blackhole;
};