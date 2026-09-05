#include "../include/opengl_error.h"
#include "../include/shader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void bind_shader(const char *file_path, unsigned int shader_id) {
        // this function is only run by the constructor to load the shaders from
        // the file path args
        std::ifstream file;

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        // so exceptions will be thrown
        file.open(file_path);

        std::string code((std::istreambuf_iterator<char>(file)),
                         (std::istreambuf_iterator<char>()));

        const char *code_c_str = code.c_str();

        GLCheckError(glShaderSource(shader_id, 1, &code_c_str, NULL));

        GLCheckError(glCompileShader(shader_id));

        shader_compilation_error(shader_id);
}

void shader_compilation_error(unsigned int shader_id) {
        int success;
        char infoLog[512];
        GLCheckError(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success));
        if (!success) {
                GLCheckError(glGetShaderInfoLog(shader_id, 512, NULL, infoLog));
                std::cerr << infoLog << std::endl;
                throw std::runtime_error("Error: Shader compilation failed\n");
        }
}

Shader::Shader(const char *vert_path, const char *frag_path) {
        unsigned int vert_shader = glCreateShader(GL_VERTEX_SHADER);
        unsigned int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

        bind_shader(vert_path, vert_shader);
        bind_shader(frag_path, frag_shader);

        unsigned int shader_program = glCreateProgram();

        GLCheckError(glAttachShader(shader_program, vert_shader));
        GLCheckError(glAttachShader(shader_program, frag_shader));
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
        // GLCheckError(glDeleteShader(vert_shader));
        // GLCheckError(glDeleteShader(frag_shader));
        // why am I deleting the shaders???
        this->programID = shader_program;
}

void Shader::apply() const { GLCheckError(glUseProgram(this->programID)); }
