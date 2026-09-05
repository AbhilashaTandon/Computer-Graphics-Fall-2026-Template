#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H
#include "gl_lib.h"
#include <string>
#include <vector>

struct VertexAttrib {
        std::string label;
        unsigned int count; // num elements
        GLenum type;        // type of elements
        bool normalized;    // if true auto normalizes floats
};

class VertexBufferLayout {
      public:
        VertexBufferLayout();
        void Bind();
        static unsigned int GetTypeSize(GLenum type);
        void Unbind();
        void AddAttrib(std::string label, unsigned int count, GLenum type,
                       bool normalized);

        const std::vector<VertexAttrib> &GetAttribs() const { return attribs; }
        inline unsigned int GetStride() const { return stride; }

      private:
        std::vector<VertexAttrib> attribs;
        unsigned int stride;
};

#endif
