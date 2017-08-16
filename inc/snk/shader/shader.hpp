#ifndef SNAKE_SHADER_HEADER
#define SNAKE_SHADER_HEADER

#include <string>
#include <GL/gl.h>

namespace snk {

/// Class encapsulating OpenGL shader program.
class Shader {
public:

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    virtual ~Shader();

protected:

    void bind() const;
    void unbind() const;

    GLint getAttribute(const std::string& attribute) const;
    GLint getUniform(const std::string& uniform) const;

private:

    void initProgram(const std::string& vertexPath, const std::string& fragmentPath);
    void destroyProgram();

private:

    GLuint mProgramId;

};

GLuint loadShader(const std::string& path, GLenum shaderType);
std::string getContents(const std::string& path);
std::string getProgramLog(GLuint programId);
std::string getShaderLog(GLuint shaderId);

} // namespace snk

#endif
