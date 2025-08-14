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


Scene::Scene(int width, int height, const char* title) {
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

    camera = new Camera(width, height);
}

Scene::~Scene() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
    delete camera;
}


void Scene::putWindowIntheCenter() {
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

void Scene::draw() {
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // does the camera and light stuff here
        camera->use();
    
        // Call the user-defined draw function if set
        if (drawFunction) {
            drawFunction(this);
        }
    
    
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Camera::Camera(int width, int height) {
    posX = 0.0f; posY = 0.0f; posZ = 5.0f;
    targetX = 0.0f; targetY = 0.0f; targetZ = 0.0f;
    upX = 0.0f; upY = 1.0f; upZ = 0.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Camera::use() {    
    gluLookAt(
        posX, posY, posZ,
        targetX, targetY, targetZ,
        upX, upY, upZ              
    );
}