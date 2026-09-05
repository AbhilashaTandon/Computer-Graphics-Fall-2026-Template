#ifndef MAIN_H
#define MAIN_H
#include "gl_lib.h"
#include "opengl_error.h"
#include <iomanip>
#include <sstream>
#include <string>

GLFWwindow *MakeWindow(unsigned int width, unsigned int height,
                       std::string title);
void GLInit();
void ProcessInput(GLFWwindow *window);
void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
void UpdateFramerate(GLfloat time_val, float &last_frame,
                     float &moving_framerate_average, float framerate_smoothing,
                     GLFWwindow *window);

void GLInit() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow *MakeWindow(unsigned int width, unsigned int height,
                       std::string title) {
        GLFWwindow *window =
            glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (window == NULL) {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
        return window;
}

void ProcessInput(GLFWwindow *window)
// process keyboard input
{
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
        }
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
// updates opengl coordinates on window resize
{
        GLCheckError(glViewport(0, 0, width, height));
}

void UpdateFramerate(GLfloat time_val, float &last_frame,
                     float &moving_framerate_average, float framerate_smoothing,
                     GLFWwindow *window) {
        float current_framerate = 1.f / (time_val - last_frame);
        moving_framerate_average =
            moving_framerate_average * framerate_smoothing +
            current_framerate * (1.f - framerate_smoothing);

        last_frame = time_val;

        std::stringstream framerate;
        framerate << std::fixed << std::setprecision(1)
                  << moving_framerate_average << " FPS";

        glfwSetWindowTitle(window, framerate.str().c_str());
}

#endif
