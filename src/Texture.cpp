//
//  Texture.cpp
//  CGProj
//

#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::chooseImage(const char* path)
{
    _text = SOIL_load_image(path, &_width, &_height, &_channels, SOIL_LOAD_RGBA);
}

void Texture::generateTexture()
{
    glGenTextures(1, &_textureName);
    glBindTexture(GL_TEXTURE_2D, _textureName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _text);
    SOIL_free_image_data(_text);
}

void Texture::bindTexture() 
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureName);
}

bool Texture::isNull()
{
	return _text == 0;
}


