#include <GL/glew.h>
#include <iostream>
#include "error/glexception.hpp"
#include "shader/basic.hpp"

namespace snk {

BasicShader::BasicShader(float width, float height)
: Shader("res/shader/snake.glvs", "res/shader/snake.glfs"),
  mViewID(0),
  mModelID(0),
  mVertexPosID(0),
  mTextureCoordID(0) {

    initVars();
    initSampler();
    initProjection(0.f, width, 0.f, height);

    Transform t;
    setModel(t);
    setView(t);

}


GLuint BasicShader::initVAO(GLuint vertexBuffer, GLuint coordBuffer, GLuint indexBuffer) const {

    GLuint newVAO;
    glGenVertexArrays(1, &newVAO);
    glBindVertexArray(newVAO);

    // Vertex positions.
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(mVertexPosID);
    glVertexAttribPointer(mVertexPosID, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Texture Coords.
    glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
    glEnableVertexAttribArray(mTextureCoordID);
    glVertexAttribPointer(mTextureCoordID, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Indices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glBindVertexArray(0);

    checkGLError("Initialising VAO");

    return newVAO;

}


void BasicShader::render(GLuint VAOID, GLuint textureID) const {

    // Bind and render target texture.
    bind();
    glBindVertexArray(VAOID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    unbind();

    // Check errors.
    // TODO: Could be beneficial to make error checking more efficient here
    // due to many render calls: remove function call and string creation
    // for every call.
    checkGLError("Rendering");

}


void BasicShader::setModel(const Transform& t) const {

    bind();
    glUniformMatrix4fv(mModelID, 1, GL_FALSE, t.getMatrix());
    unbind();

}


void BasicShader::setView(const Transform& t) const {

    bind();
    glUniformMatrix4fv(mViewID, 1, GL_FALSE, t.getMatrix());
    unbind();
}


void BasicShader::initVars() {

    mViewID = getUniform("uView");
    mModelID = getUniform("uModel");
    mVertexPosID = getAttribute("vertexPos");
    mTextureCoordID = getAttribute("iTextureCoord");

}


void BasicShader::initSampler() const {

    GLint samplerID = getUniform("uSampler");
    bind();
    glUniform1i(samplerID, 0);
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


    GLint projectionID = getUniform("uProjection");
    bind();
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, ortho);
    unbind();

}

} // namespace snk
