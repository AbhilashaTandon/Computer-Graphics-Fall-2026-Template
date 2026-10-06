#include "../include/renderer.h"

void Renderer::Clear(glm::vec4 color) const {
        GLCheckError(glClearColor(color.r, color.g, color.b, color.a));
        GLCheckError(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::DrawIndices(const VertexArray &va, const Shader &shader,
                    const IndexBuffer &ib) const {
        va.Bind();
        ib.Bind();
        shader.apply();
        GLCheckError(glDrawElements(GL_TRIANGLES, ib.GetCount(),
                                    GL_UNSIGNED_INT, nullptr));
}


void Renderer::DrawVertices(const VertexArray &va, const Shader &shader, GLsizei num_triangles) const {
        va.Bind();
        shader.apply();
        GLCheckError(glDrawArrays(GL_TRIANGLES, 0, num_triangles));
}
