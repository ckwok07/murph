#define GLFW_INCLUDE_NONE
#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>

Application::Application()
    : window(nullptr) {
}

Application::~Application() {
    shutdown();
}

bool Application::init() {
    if (!glfwInit()) {
        std::cerr << "failed init\n";
        return false;
    }
    window = glfwCreateWindow(800, 600, "murph", nullptr, nullptr);

    if (!window) {
        std::cerr << "failed window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "failed glad\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }
    // std::cout << "GPU renderer: " << glGetString(GL_RENDERER) << "\n";
    // std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

    return true;
}

int Application::run() {
    if (!init()) {
        return -1;
    }

    loop();
    return 0;
}

void Application::loop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
}

void Application::shutdown() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    glfwTerminate();
}