#ifndef MESH_H
#define MESH_H
#include "gl_lib.h"
#include "shader.h"
#include <string>

struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
};

struct ModelTexture{
    unsigned int id;
    std::string type;
    std::string path;  // we store the path of the texture to compare with other textures
};


class Mesh {
      public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<ModelTexture> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
             std::vector<ModelTexture> textures);
        void Draw(Shader &shader);

      private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};

#endif
