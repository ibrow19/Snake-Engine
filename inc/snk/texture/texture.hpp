#ifndef SNAKE_TEXTURE_HEADER
#define SNAKE_TEXTURE_HEADER

#include <string>
#include <vector>
#include <GL/gl.h>
#include <snk/shader/basic.hpp>
#include <snk/resource/resource.hpp>
#include <snk/identifiers.hpp>

namespace snk {

class Texture : public Resource {
public:

    struct clip {
    
        GLfloat left;
        GLfloat top;
        GLfloat width;
        GLfloat height;
    
    };

public:

    // TODO: Add conversion of  NPOT textures to use POT space.
    Texture();

    void reset();

    /// Initialise texture.
    /// \param shader shader to use to initialise and render texture.
    /// \param path file path of texture to load.
    void init(BasicShader& shader, const std::string& path);

    /// Register a clip that can be rendered.
    /// \param newClip texture clip to register.
    void addClip(const clip& newClip);

    /// Render transformed texture clip.
    /// \param model transform to use for rendering.
    /// \param clip texture clip to render.
    void render(const Transform& model, ClipId clip = 0);

    void destroy();

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
    void setClip(ClipId clip);
    void initVbo();
    void initIbo();

private:

    BasicShader* mShader;

    /// Vertex array object ID.
    GLuint mVaoId;

    /// Vertex buffer object ID.
    /// Stores attributes: vertex positions and texture coordinates.
    GLuint mVboId[2];

    /// Index buffer object ID.
    GLuint mIboId;

    /// Texture buffer object ID.
    GLuint mTextureId;

    GLuint mWidth;
    GLuint mHeight;

    ClipId mCurrentClip;
    std::vector<clip> mClips;

};

} // namespace snk

#endif
