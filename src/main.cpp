#include<iostream>
#include<cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include "graphics/draw.h"

using namespace std;

// Window dimensions
const int WIDTH = 1920;
const int HEIGHT = 1080;

// Sphere parameters
const float RADIUS = 0.3f;
const int SLICES = 20;
const int STACKS = 20;

// Camera parameters
float angle = 0.0f;
float camDistance = 2.0f;



void drawSphere() {
    glColor3f(1.0f, 0.5f, 2.0f); // Orange color
    
    for (int i = 0; i < STACKS; ++i) {
        float phi1 = M_PI * (float)i / STACKS;
        float phi2 = M_PI * (float)(i + 1) / STACKS;
        
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= SLICES; ++j) {
            float theta = 2.0f * M_PI * (float)j / SLICES;
            
            // First vertex (phi1)
            float x1 = RADIUS * sin(phi1) * cos(theta);
            float y1 = RADIUS * sin(phi1) * sin(theta);
            float z1 = RADIUS * cos(phi1);
            glNormal3f(x1/RADIUS, y1/RADIUS, z1/RADIUS);
            glVertex3f(x1, y1, z1);
            
            // Second vertex (phi2)
            float x2 = RADIUS * sin(phi2) * cos(theta);
            float y2 = RADIUS * sin(phi2) * sin(theta);
            float z2 = RADIUS * cos(phi2);
            glNormal3f(x2/RADIUS, y2/RADIUS, z2/RADIUS);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
}

void display(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set up camera
    gluLookAt(
        camDistance * sin(angle), 0.0f, camDistance * cos(angle), // Camera position
        0.0f, 0.0f, 0.0f,                                       // Look at origin
        0.0f, 2.5f, 0.0f                                        // Up vector
    );
    
    // Simple lighting
    GLfloat lightPos[] = { -5.0f, 5.0f, 5.0f, 0.0f };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    drawSphere();
    
    glfwSwapBuffers(window);
}





int main() {
    Window window(1920, 1080, "Physics Simulation");

    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)WIDTH / HEIGHT, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window.window)) {
        glClearColor(0.08f, 0.12f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        angle += 0.01f;
        if (angle > 2 * M_PI) angle -= 2 * M_PI;

        display(window.window);



        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }


    return 0;
}