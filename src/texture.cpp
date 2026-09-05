#include "../include/texture.h"

#include "../include/external/stb_image.h"

Texture::Texture(const std::string file_path)
    : id(0), file_path(file_path), local_buffer(nullptr), width(0), height(0),
      num_bits(0) {
        stbi_set_flip_vertically_on_load(1);
        // for some reason opengl expects textures to start at bottom left so we
        // need to flip it
        local_buffer =
            stbi_load(file_path.c_str(), &width, &height, &num_bits, 4);
        assert(local_buffer != nullptr);
        GLCheckError(glGenTextures(1, &id));
        GLCheckError(glBindTexture(GL_TEXTURE_2D, id));

        // we need to specify these 4 parameters for the texture to work
        GLCheckError(
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCheckError(
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                                     GL_CLAMP_TO_EDGE));
        GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                                     GL_CLAMP_TO_EDGE));

        GLCheckError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
                                  GL_RGBA, GL_UNSIGNED_BYTE, local_buffer));
        // the GL_RGBA here corresponds to the format we're giving the image in,
        // the GL_RGBA8 argument corresponds to the internal format we want
        // OpenGL to use for our texture
        GLCheckError(glBindTexture(GL_TEXTURE_2D, 0));

        if (local_buffer) {
                stbi_image_free(local_buffer);
                // removes data from CPU side
                // note sometimes we would want to keep this
        }
}

Texture::~Texture() { GLCheckError(glDeleteTextures(1, &id)); }

void Texture::Bind(unsigned int slot) const {
        GLCheckError(glActiveTexture(GL_TEXTURE0 + slot));
        GLCheckError(glBindTexture(GL_TEXTURE_2D, id));
}

void Texture::Unbind() const { GLCheckError(glBindTexture(GL_TEXTURE_2D, 0)); }
