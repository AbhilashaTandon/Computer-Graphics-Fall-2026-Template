#include "../include/gl_lib.h"
#include "../include/opengl_error.h"
#include "../include/vertex_array.h"

VertexArray::VertexArray() { GLCheckError(glGenVertexArrays(1, &id)); }

VertexArray::~VertexArray() { GLCheckError(glDeleteVertexArrays(1, &id)); }

void VertexArray::AddBuffer(const VertexBuffer &vb,
                            const VertexBufferLayout &layout) {
        Bind();
        vb.Bind();
        const auto &attribs = layout.GetAttribs();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < attribs.size(); i++) {
                const auto &attrib = attribs[i];
                GLCheckError(glEnableVertexAttribArray(i));
                GLCheckError(glVertexAttribPointer(
                    i, attrib.count, attrib.type,
                    attrib.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                    (const void *)offset));
                offset += layout.GetTypeSize(attrib.type) * attrib.count;
        }
}

void VertexArray::Bind() const { GLCheckError(glBindVertexArray(id)); }

void VertexArray::Unbind() const { GLCheckError(glBindVertexArray(0)); }
