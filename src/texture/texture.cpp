#include <cassert>
#include <GL/glew.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <snk/error/sdlexception.hpp>
#include <snk/error/glexception.hpp>
#include <snk/texture/texture.hpp>

namespace snk {

Texture::Texture() 
: mShader(nullptr),
  mVaoId(0),
  mVboId{0},
  mIboId(0),
  mTextureId(0),
  mWidth(0),
  mHeight(0),
  mCurrentClip(0) {}


Texture::~Texture() {

    destroyTexture();

}


void Texture::reset() {

    destroyTexture();
    mShader = nullptr;
    mVaoId = 0;
    mVboId[0] = 0;
    mVboId[1] = 0;
    mIboId = 0;
    mTextureId = 0;
    mWidth = 0;
    mHeight = 0;
    mCurrentClip = 0;
    mClips.clear();

}


void Texture::init(BasicShader& shader, const std::string& path) {

    assert(mShader == nullptr);
    mShader = &shader;

    loadFromFile(path);
    initVbo();
    initIbo();
    mVaoId = mShader->initVao(mVboId[0], mVboId[1], mIboId);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {

        throw GLException("Error initialisng texture: " + path, error);

    }

    // Add default clip for entire texture. 
    addClip({0.f, 0.f, (GLfloat)mWidth, (GLfloat)mHeight});

}


void Texture::addClip(const clip& newClip) {

    assert(mShader != nullptr);
    mClips.push_back(newClip);

}


void Texture::setClip(unsigned int clipIndex) {

    assert(clipIndex < mClips.size());

    clip& target = mClips[clipIndex];
    GLfloat left = target.left / mWidth;;
    GLfloat right = (target.left + target.width) / mWidth;
    GLfloat top = target.top / mHeight;
    GLfloat bottom = (target.top + target.height) / mHeight;
    GLfloat width = target.width;
    GLfloat height = target.height;

    VertexPos vertices[4];
    TextureCoord coords[4];

    vertices[0].x = 0.f;
    vertices[0].y = 0.f;
    coords[0].s = left;
    coords[0].t = top;

    vertices[1].x = width;
    vertices[1].y = 0.f;
    coords[1].s = right;
    coords[1].t = top;

    vertices[2].x = width;
    vertices[2].y = height;
    coords[2].s = right;
    coords[2].t = bottom;

    vertices[3].x = 0.f;
    vertices[3].y = height;
    coords[3].s = left;
    coords[3].t = bottom;

    // Fill first buffer with vertex positions.
    glBindBuffer(GL_ARRAY_BUFFER, mVboId[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(VertexPos), vertices);

    // Fill second buffer with texture coordinates.
    glBindBuffer(GL_ARRAY_BUFFER, mVboId[1]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(TextureCoord), coords);
    
    //Unbind buffer.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}


void Texture::render(const Transform& model, unsigned int clip) {

    assert(mShader != nullptr);
    mShader->setModel(model);
    if (mCurrentClip != clip) {

        setClip(clip);
        mCurrentClip = clip;

    }
    mShader->render(mVaoId, mTextureId);

}


void Texture::loadFromFile(const std::string& path) {

    SDL_Surface* loaded = IMG_Load(path.c_str());
    if (loaded == nullptr) {

        throw SDLException();

    }

    mWidth = loaded->w;
    mHeight = loaded->h;

    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId);

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
    // Use linear sampling.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Repeat textures when wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Unbind.
    glBindTexture(GL_TEXTURE_2D, 0);
    
    SDL_FreeSurface(loaded);

}


void Texture::initVbo() {

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
    glGenBuffers(2, mVboId);

    // Fill first buffer with vertex positions.
    glBindBuffer(GL_ARRAY_BUFFER, mVboId[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexPos), vertices, GL_DYNAMIC_DRAW);

    // Fill second buffer with texture coordinates.
    glBindBuffer(GL_ARRAY_BUFFER, mVboId[1]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(TextureCoord), coords, GL_DYNAMIC_DRAW);
    
    //Unbind buffer.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}


void Texture::initIbo() {

    GLuint indices[4] = {0, 1, 2, 3};

    glGenBuffers(1, &mIboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);
    
    //Unbind buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


void Texture::destroyTexture() {

    glDeleteVertexArrays(1, &mVaoId); 
    glDeleteBuffers(2, mVboId); 
    glDeleteBuffers(1, &mIboId);
    glDeleteBuffers(1, &mTextureId);

}

} // namespace snk
