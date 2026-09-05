#include "../include/renderer.h"

void Renderer::Clear(glm::vec4 color) const {
        GLCheckError(glClearColor(color.r, color.g, color.b, color.a));
        GLCheckError(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray &va, const Shader &shader,
                    const IndexBuffer &ib) const {
        va.Bind();
        ib.Bind();
        shader.apply();
        GLCheckError(glDrawElements(GL_TRIANGLES, ib.GetCount(),
                                    GL_UNSIGNED_INT, nullptr));
}
