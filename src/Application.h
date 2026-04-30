#pragma once

#include <GLFW/glfw3.h>
#include "Renderer.h"

class Application {
public:
    Application();
    ~Application();

    int run();

private:
    bool init();
    void loop();
    void shutdown();

private:
    GLFWwindow* window;
    Renderer renderer;
};