#pragma once
#include "opengl_error.h"
#include <string>

#include "gl_lib.h"

class Shader {
      public:
        Shader(const char *vert_path, const char *frag_path);
        inline GLuint get_id() const { return this->programID; }
        void setBool(const std::string &name, bool value) const {
                GLCheckError(glUniform1i(
                    glGetUniformLocation(this->programID, name.c_str()),
                    (int)value));
        }
        // ------------------------------------------------------------------------
        void setInt(const std::string &name, int value) const {
                GLCheckError(glUniform1i(
                    glGetUniformLocation(this->programID, name.c_str()),
                    value));
        }
        // ------------------------------------------------------------------------
        void setFloat(const std::string &name, float value) const {
                GLCheckError(glUniform1f(
                    glGetUniformLocation(this->programID, name.c_str()),
                    value));
        }
        // ------------------------------------------------------------------------
        void setVec2(const std::string &name, const glm::vec2 &value) const {
                GLCheckError(glUniform2fv(
                    glGetUniformLocation(this->programID, name.c_str()), 1,
                    &value[0]));
        }
        void setVec2(const std::string &name, float x, float y) const {
                GLCheckError(glUniform2f(
                    glGetUniformLocation(this->programID, name.c_str()), x, y));
        }
        // ------------------------------------------------------------------------
        void setVec3(const std::string &name, const glm::vec3 &value) const {
                GLCheckError(glUniform3fv(
                    glGetUniformLocation(this->programID, name.c_str()), 1,
                    &value[0]));
        }
        void setVec3(const std::string &name, float x, float y, float z) const {
                GLCheckError(glUniform3f(
                    glGetUniformLocation(this->programID, name.c_str()), x, y,
                    z));
        }
        // ------------------------------------------------------------------------
        void setVec4(const std::string &name, const glm::vec4 &value) const {
                GLCheckError(glUniform4fv(
                    glGetUniformLocation(this->programID, name.c_str()), 1,
                    &value[0]));
        }
        void setVec4(const std::string &name, float x, float y, float z,
                     float w) {
                GLCheckError(glUniform4f(
                    glGetUniformLocation(this->programID, name.c_str()), x, y,
                    z, w));
        }
        // ------------------------------------------------------------------------
        void setMat2(const std::string &name, const glm::mat2 &mat) const {
                GLCheckError(glUniformMatrix2fv(
                    glGetUniformLocation(this->programID, name.c_str()), 1,
                    GL_FALSE, &mat[0][0]));
        }
        // ------------------------------------------------------------------------
        void setMat3(const std::string &name, const glm::mat3 &mat) const {
                GLCheckError(glUniformMatrix3fv(
                    glGetUniformLocation(this->programID, name.c_str()), 1,
                    GL_FALSE, &mat[0][0]));
        }
        // ------------------------------------------------------------------------
        void setMat4(const std::string &name, const glm::mat4 &mat) const {
                GLCheckError(glUniformMatrix4fv(
                    glGetUniformLocation(this->programID, name.c_str()), 1,
                    GL_FALSE, &mat[0][0]));
        }
        void apply() const;

      private:
        unsigned int programID;
};

void bind_shader(const char *file_path, unsigned int shader_id);

void shader_compilation_error(unsigned int shader_id);
