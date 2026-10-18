#include "../include/util.h"

#include "../include/gl_lib.h"
#include "../include/opengl_error.h"
#include <iomanip>
#include <sstream>
#include <string>

void report_file_error(const char *&file_path, std::ifstream &file) {
        if (!file.is_open()) {
                std::cerr << "Error opening file: \"" << file_path << "\"";

                if (file.fail()) {
                        // Print a more detailed error message using
                        // strerror
                        std::cerr << ". " << std::strerror(errno) << std::endl;
                }

                // Check for specific error conditions
                if (file.bad()) {
                        std::cerr << "Fatal error: badbit is set." << std::endl;
                }
        }
}

void show_compute_shader_info() {
        GLint work_group_count[3];
        for (int i = 0; i < 3; i++) {
                work_group_count[i] = 0;
        }
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0,
                        &work_group_count[0]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1,
                        &work_group_count[1]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2,
                        &work_group_count[2]);
        // work group size
        GLint work_group_size[3];
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_group_size[0]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_group_size[1]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_group_size[2]);

        GLint work_group_inv;
        glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_group_inv);

        std::cout << " total work group count x : " << work_group_count[0]
                  << "\n";
        std::cout << " total work group count y : " << work_group_count[1]
                  << "\n";
        std::cout << " total work group count z : " << work_group_count[2]
                  << "\n";
        std::cout << " total work group size x : " << work_group_size[0]
                  << "\n";
        std::cout << " total work group size y : " << work_group_size[1]
                  << "\n";
        std::cout << " total work group size z : " << work_group_size[2]
                  << "\n";
        std::cout << " max work group invocation : " << work_group_inv << "\n";
}

void GLInit() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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
