#include<GLFW/glfw3.h>
#include<iostream>
#include "draw.h"


Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        throw "Failed to initialize GLFW";
    }
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw "Failed to create GLFW window";
    }
    
    putWindowIntheCenter();
    glfwMakeContextCurrent(window);

    // Set viewport
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

}

Window::~Window() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}


void Window::putWindowIntheCenter() {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) return;

    std::cout << "Monitor: " << monitor << std::endl;

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) return;

    std::cout << "Video Mode: " << mode->width << "x" << mode->height << std::endl;

    int monitorX, monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);


    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    int posX = monitorX + (mode->width - windowWidth) / 2;
    int posY = monitorY + (mode->height - windowHeight) / 2;

    glfwSetWindowPos(window, posX, posY);
}