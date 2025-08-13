#pragma once
#include<GLFW/glfw3.h>

class Scene {
public:
    GLFWwindow* window;
    Scene(int width, int height, const char* title);
    ~Scene();
private:
    void putWindowIntheCenter();
};
