#pragma once
#include<GLFW/glfw3.h>

class Window {
public:
    GLFWwindow* window;
    Window(int width, int height, const char* title);
    ~Window();
    void loop();
};
