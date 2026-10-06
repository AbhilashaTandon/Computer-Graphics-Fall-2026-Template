#ifndef RENDERER_H
#define RENDERER_H

#include "gl_lib.h"
#include "index_buffer.h"
#include "opengl_error.h"
#include "shader.h"
#include "vertex_array.h"

class Renderer {
      public:
        void Clear(glm::vec4 color) const;
        void DrawIndices(const VertexArray &va, const Shader &shader,
                  const IndexBuffer &ib) const;

        void DrawVertices(const VertexArray &va, const Shader &shader, GLsizei num_triangles) const;
};

#endif
