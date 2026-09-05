#include "../include/gl_lib.h"
#include "../include/opengl_error.h"
#include "../include/vertex_buffer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
        GLCheckError(glGenBuffers(1, &id));              // buffers
        GLCheckError(glBindBuffer(GL_ARRAY_BUFFER, id)); // buffer
        GLCheckError(glBufferData(GL_ARRAY_BUFFER, size, data,
                                  GL_STATIC_DRAW)); // buffer
}

VertexBuffer::~VertexBuffer() { GLCheckError(glDeleteBuffers(1, &id)); }

void VertexBuffer::Bind() const {
        GLCheckError(glBindBuffer(GL_ARRAY_BUFFER, id)); // buffer
}

void VertexBuffer::Unbind() const {
        GLCheckError(glBindBuffer(GL_ARRAY_BUFFER, 0)); // buffer
}
