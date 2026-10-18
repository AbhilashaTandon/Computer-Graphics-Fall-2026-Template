#include "../include/compute_shader.h"
#include "../include/gl_lib.h"

#include "../include/opengl_error.h"
#include "../include/shader.h"


#include <cstring>
#include <iostream>
#include <stdexcept>

ComputeShader::ComputeShader(const char *compute_path) {
        unsigned int compute_shader = glCreateShader(GL_COMPUTE_SHADER);

        bind_shader(compute_path, compute_shader);

        unsigned int shader_program = glCreateProgram();

        GLCheckError(glAttachShader(shader_program, compute_shader));
        GLCheckError(glLinkProgram(shader_program));

        int success;
        char infoLog[512];
        GLCheckError(glGetProgramiv(shader_program, GL_LINK_STATUS, &success));
        if (!success) {
                GLCheckError(
                    glGetProgramInfoLog(shader_program, 512, NULL, infoLog));
                std::cerr << infoLog << std::endl;
                throw std::runtime_error("Error: shader linking failed\n");
        }

        GLCheckError(glUseProgram(shader_program));
        this->programID = shader_program;
}

void ComputeShader::apply() const {
        GLCheckError(glUseProgram(this->programID));
}
