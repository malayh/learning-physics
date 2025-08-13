#pragma once
#include<GLFW/glfw3.h>

class Window {
public:
    GLFWwindow* window;
    Window(int width, int height, const char* title);
    ~Window();
private:
    void putWindowIntheCenter();
};

void draw_rectangle(float x, float y, float width, float height);