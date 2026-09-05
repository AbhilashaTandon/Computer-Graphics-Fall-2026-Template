#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {

      public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer &vb,
                       const VertexBufferLayout &layout);

        void Bind() const;
        void Unbind() const;

      private:
        unsigned int id;
};

#endif
