#pragma once
#include<GLFW/glfw3.h>


class Camera {
public:
    float posX, posY, posZ;
    float targetX, targetY, targetZ;
    float upX, upY, upZ;
    Camera(int, int);
    void use();
};

class Scene {
public:
    GLFWwindow* window;
    Camera* camera;
    Scene(int width, int height, const char* title);
    ~Scene();
    void draw();
    void setDrawFunction(void (*drawFunction)(Scene* scene)) {
        this->drawFunction = drawFunction;
    }
private:
    void (*drawFunction)(Scene* scene);
    void putWindowIntheCenter();
};


