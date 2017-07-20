#include <GL/glew.h>
#include <iostream>
#include <error/glexception.hpp>
#include <shader/basic.hpp>

namespace snk {

BasicShader::BasicShader(float width, float height)
: Shader("res/shader/snake.glvs", "res/shader/snake.glfs"),
  mViewId(0),
  mModelId(0),
  mVertexPosId(0),
  mTextureCoordId(0) {

    initVars();
    initSampler();
    initProjection(0.f, width, 0.f, height);

    Transform t;
    setModel(t);
    setView(t);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {

        throw GLException("Error initialisng basic shader", error);

    }

}


GLuint BasicShader::initVao(GLuint vertexBuffer, GLuint coordBuffer, GLuint indexBuffer) const {

    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    // Vertex positions.
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(mVertexPosId);
    glVertexAttribPointer(mVertexPosId, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Texture Coords.
    glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
    glEnableVertexAttribArray(mTextureCoordId);
    glVertexAttribPointer(mTextureCoordId, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Indices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glBindVertexArray(0);

    return vaoId;

}


void BasicShader::render(GLuint vaoId, GLuint textureId) const {

    // Bind and render target texture.
    bind();
    glBindVertexArray(vaoId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);

    // TODO: avoiding unbinding here to try and optimise draws.
    //       This is assuming OpenGL will not rebind something
    //       if it is already bound. This is true for most
    //       implementations but it would probaby be better to
    //       track what is bound and handle optimisation client side.

}


void BasicShader::setModel(const Transform& t) const {

    bind();
    glUniformMatrix4fv(mModelId, 1, GL_FALSE, t.getMatrix());
    unbind();

}


void BasicShader::setView(const Transform& t) const {

    bind();
    glUniformMatrix4fv(mViewId, 1, GL_FALSE, t.getMatrix());
    unbind();
}


void BasicShader::initVars() {

    mViewId = getUniform("uView");
    mModelId = getUniform("uModel");
    mVertexPosId = getAttribute("vertexPos");
    mTextureCoordId = getAttribute("iTextureCoord");

}


void BasicShader::initSampler() const {

    GLint samplerId = getUniform("uSampler");
    bind();
    glUniform1i(samplerId, 0);
    unbind();

}


void BasicShader::initProjection(float left, float right, float top, float bottom) const {

    float c00 = 2.f / (right - left);
    float c11 = 2.f / (top - bottom);
    float c22 = -1.f;

    float c30 = -(right + left) / (right - left);
    float c31 = -(top + bottom) / (top - bottom);

    float ortho[16] = {c00, 0.f, 0.f, 0.f,
                       0.f, c11, 0.f, 0.f,
                       0.f, 0.f, c22, 0.f, 
                       c30, c31, 0.f, 1.f};


    GLint projectionId = getUniform("uProjection");
    bind();
    glUniformMatrix4fv(projectionId, 1, GL_FALSE, ortho);
    unbind();

}

} // namespace snk
