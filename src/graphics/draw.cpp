#include<GLFW/glfw3.h>
#include<GL/glu.h>
#include "draw.h"


static void window_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}


Window::Window(int width, int height, const char* title) {
    if (!glfwInit()) {
        throw "Failed to initialize GLFW";
    }
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwSetFramebufferSizeCallback(window, window_resize_callback);

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

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) return;

    int monitorX, monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);


    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    int posX = monitorX + (mode->width - windowWidth) / 2;
    int posY = monitorY + (mode->height - windowHeight) / 2;

    glfwSetWindowPos(window, posX, posY);
}