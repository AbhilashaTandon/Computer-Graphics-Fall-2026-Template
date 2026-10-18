
#ifndef UTIL_H
#define UTIL_H
#include "gl_lib.h"
#include "opengl_error.h"
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

void report_file_error(const char *&file_path, std::ifstream &file);

void show_compute_shader_info();

void GLInit();

GLFWwindow *MakeWindow(unsigned int width, unsigned int height,
                       std::string title);

void ProcessInput(GLFWwindow *window);
// process keyboard input

void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
// updates opengl coordinates on window resize

void UpdateFramerate(GLfloat time_val, float &last_frame,
                     float &moving_framerate_average, float framerate_smoothing,
                     GLFWwindow *window);

#endif
