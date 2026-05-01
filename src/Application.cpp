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
        float dx = 0.5 * float(x - lastX);
        float dy = 0.5 * float(lastY - y);
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

    glEnable(GL_PROGRAM_POINT_SIZE);

    Particle p;
    p.position = glm::vec3(1.0f, 0.0f, 0.0f);
    p.velocity = glm::vec3(0.0f);
    p.acceleration = glm::vec3(0.0f);
    p.mass = 1.0f;
    p.size = 1.0f;
    physics.addParticle(p);

    Particle p2;
    p2.position = glm::vec3(0.0f, 0.0f, 1.0f);
    p2.velocity = glm::vec3(0.0f);
    p2.acceleration = glm::vec3(0.0f);
    p2.mass = 1.0f;
    p2.size = 1.0f;
    physics.addParticle(p2);

    Particle p3;
    p3.position = glm::vec3(0.0f, 1.0f, 0.0f);
    p3.velocity = glm::vec3(0.0f);
    p3.acceleration = glm::vec3(0.0f);
    p3.mass = 1.0f;
    p3.size = 1.0f;
    physics.addParticle(p3);
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
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double now = glfwGetTime();
        float dt = float(now - lastTime);
        lastTime = now;
        glfwPollEvents();

        renderer.camera.keyEvent(
            glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS,
            glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS,
            dt);
        
        physics.update(dt);
        // renderer.clear();
        // renderer.draw(physics.particles);
        renderer.drawRaymarch();
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