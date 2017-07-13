#ifndef SNAKE_TEXTURE_HEADER
#define SNAKE_TEXTURE_HEADER

#include <string>
#include <vector>
#include <GL/gl.h>
#include "shader/basic.hpp"

namespace snk {

// TODO: define number of vertices for definng size of vertex, textureCoord, index arrays etc.
// potentially in header fo structs.
// TODO: move structs to separate header.
struct VertexPos {

    GLfloat x;
    GLfloat y;

};

struct TextureCoord {

    GLfloat s;
    GLfloat t;

};

struct clip {

    GLfloat left;
    GLfloat top;
    GLfloat width;
    GLfloat height;

};

class Texture {
public:

    // TODO: Add conversion of  NPOT textures to use POT space.
    Texture(BasicShader& shader, const std::string& path);
    ~Texture();

    void addClip(const clip& newClip);
    void render();
    void render(unsigned int clip);

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
