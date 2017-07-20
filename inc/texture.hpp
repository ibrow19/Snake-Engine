#ifndef SNAKE_TEXTURE_HEADER
#define SNAKE_TEXTURE_HEADER

#include <string>
#include <vector>
#include <GL/gl.h>
#include <shader/basic.hpp>

namespace snk {

class Texture {
public:

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
    void render(const Transform& model, unsigned int clip = 0);

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
    void initVbo();
    void initIbo();
    void destroyTexture();

private:

    BasicShader& mShader;

    /// Vertex array object ID.
    GLuint mVaoId;

    // TODO: these could be split into separate variables for clarity.
    /// Vertex buffer object ID.
    /// Stores attributes: vertex positions and texture coordinates.
    GLuint mVboId[2];

    /// Index buffer object ID.
    GLuint mIboId;

    /// Texture buffer object ID.
    GLuint mTextureId;

    GLuint mWidth;
    GLuint mHeight;

    unsigned int currentClip;
    std::vector<clip> clips;

};

} // namespace snk

#endif
