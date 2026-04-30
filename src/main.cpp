#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>

int main() {
    if (!glfwInit()) {
        std::cerr << "failed init\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "murph", nullptr, nullptr);

    if (!window) {
        std::cerr << "failed window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "failed glad\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    std::cout << "GPU renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}