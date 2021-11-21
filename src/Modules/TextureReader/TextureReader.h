#ifndef TEXTUREREADER_H
#define TEXTUREREADER_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GL/glew.h"
#include <cinttypes>

uint32_t load_texture(const char* path, 
    uint32_t wrap_mode, uint32_t filter_mode)
{
    int width, height, channels;
    uint32_t gl_id;

    stbi_set_flip_vertically_on_load(1);
    unsigned char* tex_src = new unsigned char[2048];
    tex_src = stbi_load(path, &width, &height, &channels, 0);

    glGenTextures(1, &gl_id);
    glBindTexture(GL_TEXTURE_2D, gl_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_mode);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
        channels == 4 ? GL_RGBA : GL_RGB,
        GL_UNSIGNED_BYTE,
        tex_src);

    delete [] tex_src;
    glBindTexture(GL_TEXTURE_2D, 0);
    return gl_id;
}

#endif