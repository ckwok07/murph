#define GLFW_INCLUDE_NONE
#include "Application.h"
struct GLFWwindow;
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
    window = glfwCreateWindow(800, 800, "murph", nullptr, nullptr);

    if (!window) {
        std::cerr << "failed window\n";
        glfwTerminate();
        return false;
    }
    glfwSetWindowUserPointer(window, this);

    glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y) {
        auto* app = static_cast<Application*>(glfwGetWindowUserPointer(w));
        static double lastX = x, lastY = y;
        float dx = float(x - lastX);
        float dy = float(lastY - y);
        lastX = x;
        lastY = y;
        app->renderer.camera.mouseEvent(dx, dy);
    });
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "failed glad\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }
    // std::cout << "GPU renderer: " << glGetString(GL_RENDERER) << "\n";
    // std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

    if (!renderer.init()) {
        std::cerr << "failed renderer init\n";
        return false;
    }

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
        renderer.clear();
        glfwSwapBuffers(window);
    }
}

void Application::shutdown() {
    if (window) {
        renderer.shutdown();
        glfwDestroyWindow(window);
        window = nullptr;
    }

    glfwTerminate();
}

void Application::mouseEvent(float dx, float dy) {
    renderer.camera.mouseEvent(dx,dy);
}