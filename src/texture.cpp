#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include "error/sdlexception.hpp"
#include "error/glexception.hpp"
#include "texture.hpp"

namespace snk {

Texture::Texture(BasicShader& shader, const std::string& path) 
: mShader(shader),
  mVAOID(0),
  mVBOID{0},
  mIBOID(0),
  mTextureID(0),
  mWidth(0),
  mHeight(0) {

    // TODO: can probably do without all the exception throwing here.
    try {

        loadFromFile(path);
        initVBO();
        initIBO();
        mVAOID = mShader.initVAO(mVBOID[0], mVBOID[1], mIBOID);

    } catch (SDLException& e) {

        destroyTexture();
        throw;

    }
      
}


Texture::~Texture() {

    destroyTexture();

}


void Texture::render() {

    mShader.render(mVAOID, mTextureID);

}


void Texture::loadFromFile(const std::string& path) {

    SDL_Surface* loaded = IMG_Load(path.c_str());
    if (loaded == nullptr) {

        throw SDLException();

    }

    mWidth = loaded->w;
    mHeight = loaded->h;

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    // set mode to match texture format.
    int mode = GL_RGB;
    if (loaded->format->BytesPerPixel == 4) {
        mode = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 
                 0, 
                 mode, 
                 mWidth, 
                 mHeight, 
                 0, 
                 mode, 
                 GL_UNSIGNED_BYTE,
                 loaded->pixels);

    // Texture parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);

    // Unbind.
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SDL_FreeSurface(loaded);

    checkGLError();

}


void Texture::initVBO() {

    VertexPos vertices[4];
    TextureCoord coords[4];

    vertices[0].x = 0.f;
    vertices[0].y = 0.f;
    coords[0].s = 0.f;
    coords[0].t = 0.f;

    vertices[1].x = mWidth;
    vertices[1].y = 0.f;
    coords[1].s = 1.f;
    coords[1].t = 0.f;

    vertices[2].x = mWidth;
    vertices[2].y = mHeight;
    coords[2].s = 1.f;
    coords[2].t = 1.f;

    vertices[3].x = 0.f;
    vertices[3].y = mHeight;
    coords[3].s = 0.f;
    coords[3].t = 1.f;

    // Allocate two vertex buffers. One for vertex positions and one for texture coordinates.
    glGenBuffers(2, mVBOID);

    // Fill first buffer with vertex positions.
    glBindBuffer(GL_ARRAY_BUFFER, mVBOID[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexPos), vertices, GL_STATIC_DRAW);

    // Fill second buffer with texture coordinates.
    glBindBuffer(GL_ARRAY_BUFFER, mVBOID[1]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(TextureCoord), coords, GL_STATIC_DRAW);
    
    //Unbind buffer.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    checkGLError("Initialising VBO");
}


void Texture::initIBO() {

    GLuint indices[4] = {0, 1, 2, 3};

    glGenBuffers(1, &mIBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    
    //Unbind buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    checkGLError("Initialising IBO");

}


void Texture::destroyTexture() {

    glDeleteVertexArrays(1, &mVAOID); 
    glDeleteBuffers(2, mVBOID); 
    glDeleteBuffers(1, &mIBOID);
    glDeleteBuffers(1, &mTextureID);

}

} // namespace snk
