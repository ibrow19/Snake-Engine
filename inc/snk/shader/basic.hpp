#ifndef SNAKE_BASIC_SHADER_HEADER
#define SNAKE_BASIC_SHADER_HEADER

#include <snk/maths/transform.hpp>
#include <snk/shader/shader.hpp>

namespace snk {

/// Basic shader implementation.
class BasicShader : public Shader {
public:

    /// Initialise shader with window size to determine projection.
    /// \param width window width. 
    /// \param height window height. 
    BasicShader(float width, float height);

    /// Initialise a vertex array object for use with this shader.
    /// \param vertexBuffer buffer to use for vertex position attributes.
    /// \param coordBuffer buffer to use for texture coordintae attributes.
    /// \param indexBuffer buffer to use for element indices.
    GLuint initVao(GLuint vertexBuffer, GLuint coordBuffer, GLuint indexBuffer) const;

    /// Render a texture using a vertex array object initialised for this shader.
    void render(GLuint vaoId, GLuint textureId) const;

    /// Set the model matrix.
    /// \param t transform to set matrix to.
    void setModel(const Transform& t) const;

    /// Set the view matrix.
    /// \param t transform to set matrix to.
    void setView(const Transform& t) const;

private:

    /// Initialise shader variables references.
    void initVars();

    /// Initialise texture sampler.
    void initSampler() const;

    /// Initialise the projection matrix with an orthographic matrix based
    /// on the window size.
    /// \param left offset of left of window.
    /// \param right offset of right of window.
    /// \param top offset of top of window.
    /// \param bottom offset of bottom of window.
    void initProjection(float left, float right, float top, float bottom) const;

private:

    // Model and biew matrix shader uniforms.
    GLint mViewId;
    GLint mModelId;

    // Vertex and coordinate shader attributes.
    GLint mVertexPosId;
    GLint mTextureCoordId;

};

} // namespace snk

#endif
