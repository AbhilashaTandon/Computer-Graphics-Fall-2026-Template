#ifndef TEXTURE_H
#define TEXTURE_H
#include "opengl_error.h"
#include <string>

class Texture {
      public:
        Texture(const std::string file_path);
        ~Texture();

        void Bind(unsigned int slot = 0) const;
        // you can bind textures into "slots", which allows you to have multiple
        // textures there are probably like 32
        void Unbind() const;

        inline int GetWidth() const { return width; }
        inline int GetHeight() const { return height; }
        inline int GetNumBits() const { return num_bits; }

      
        unsigned int id;
        std::string file_path;
        unsigned char *local_buffer;
        int width, height, num_bits;
};

#endif
