#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer {
      private:
        unsigned int id;

      public:
        VertexBuffer(const void *data, unsigned int size);
        // size is size of data in bytes
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
};

#endif
