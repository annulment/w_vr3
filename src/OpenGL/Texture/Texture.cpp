#include "Texture.h"
#include "..//..//stb_image/stb_image.h"
#include <cassert>

w_vr3::gl::Texture::Texture(GLuint id) : id(id){
}

w_vr3::gl::Texture::Texture(const unsigned char* data, int width, int height, w_vr3::gl::w_vr3_texture_type t_type){
    create(data, width, height, t_type);
}

w_vr3::gl::Texture::Texture(){
}

void w_vr3::gl::Texture::create(const unsigned char* data, int width, int height, w_vr3::gl::w_vr3_texture_type t_type){
    assert(id != 0);

    this->width = width;
    this->height = height;
    
    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);

    switch (t_type)
    {
    case w_vr3::gl::w_vr3_texture_type_rgb:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        break;
    case w_vr3::gl::w_vr3_texture_type_rgba:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        break;
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void w_vr3::gl::Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, id);
}

void w_vr3::gl::Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

w_vr3::gl::Texture::~Texture(){
    glDeleteTextures(1, &id);
}

w_vr3::gl::Texture* w_vr3::gl::Texture::load_from_file(const std::string& file_name){
    w_vr3::gl::Texture* texture = new w_vr3::gl::Texture();
    int width, height, nrChannels;

    unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &nrChannels, 0);

    texture->create(data, width, height);

    return texture;
}

