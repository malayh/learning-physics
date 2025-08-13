#include<GLFW/glfw3.h>
#include "draw.h"
using namespace std;

Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        throw "Failed to initialize GLFW";
    }
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw "Failed to create GLFW window";
    }
    glfwMakeContextCurrent(window);
}

Window::~Window() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void Window::loop() {
    while (!glfwWindowShouldClose(window)) {
        // Render here (clear screen to a color)
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, 0, 0, 0);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
}