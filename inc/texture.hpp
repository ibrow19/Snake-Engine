#ifndef SNAKE_TEXTURE_HEADER
#define SNAKE_TEXTURE_HEADER

#include <string>
#include <vector>
#include <GL/gl.h>
#include "shader/basic.hpp"

namespace snk {

class Texture {
public:

    // TODO: use smaller data type for clips and vertex attributes.
    struct clip {
    
        GLfloat left;
        GLfloat top;
        GLfloat width;
        GLfloat height;
    
    };

public:

    // TODO: Add conversion of  NPOT textures to use POT space.
    Texture(BasicShader& shader, const std::string& path);
    ~Texture();

    void addClip(const clip& newClip);
    void render();
    void render(unsigned int clip);

private:

    struct VertexPos {
    
        GLfloat x;
        GLfloat y;
    
    };
    
    struct TextureCoord {
    
        GLfloat s;
        GLfloat t;
    
    };

private:

    void loadFromFile(const std::string& path);
    void setClip(unsigned int clip);
    void initVBO();
    void initIBO();
    void destroyTexture();

private:

    BasicShader& mShader;

    /// Vertex array object ID.
    GLuint mVAOID;

    // TODO: these could be split into separate variables for clarity.
    /// Vertex buffer object ID.
    /// Stores attributes: vertex positions and texture coordinates.
    GLuint mVBOID[2];

    /// Index buffer object ID.
    GLuint mIBOID;

    /// Texture buffer object ID.
    GLuint mTextureID;

    GLuint mWidth;
    GLuint mHeight;

    unsigned int currentClip;
    std::vector<clip> clips;

};

} // namespace snk

#endif
