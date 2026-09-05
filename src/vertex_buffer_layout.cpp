#include "../include/opengl_error.h"
#include "../include/vertex_buffer_layout.h"
#include <cstdint>

VertexBufferLayout::VertexBufferLayout() : stride(0) {}

unsigned int VertexBufferLayout::GetTypeSize(GLenum type) {
        switch (type) {
        case GL_BYTE:
                return sizeof(GLbyte);
        case GL_UNSIGNED_BYTE:
                return sizeof(GLubyte);
        case GL_SHORT:
                return sizeof(GLshort);
        case GL_UNSIGNED_SHORT:
                return sizeof(GLushort);
        case GL_INT:
                return sizeof(GLint);
        case GL_UNSIGNED_INT:
                return sizeof(GLuint);
        case GL_FLOAT:
                return sizeof(GLfloat);
        case GL_DOUBLE:
                return sizeof(GLdouble);
        default:
                std::cerr << "Unimplemented vertex attribute type!\n";
                assert(false);
        }
}

void VertexBufferLayout::AddAttrib(std::string label, unsigned int count,
                                   GLenum type, bool normalized) {
        attribs.push_back({label, count, type, normalized});
        stride += GetTypeSize(type) * count;
}
