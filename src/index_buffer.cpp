#include "../include/gl_lib.h"
#include "../include/index_buffer.h"
#include "../include/opengl_error.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
    : count(count) {
        GLCheckError(glGenBuffers(1, &id));                      // buffers
        GLCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id)); // buffer
        GLCheckError(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                  count * sizeof(unsigned int), data,
                                  GL_STATIC_DRAW)); // buffer
}

IndexBuffer::~IndexBuffer() { GLCheckError(glDeleteBuffers(1, &id)); }

void IndexBuffer::Bind() const {
        GLCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id)); // buffer
}

void IndexBuffer::Unbind() const {
        GLCheckError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // buffer
}
