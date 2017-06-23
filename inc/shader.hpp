#ifndef SNAKE_SHADER_HEADER
#define SNAKE_SHADER_HEADER

#include <string>
#include <GL/gl.h>

namespace snk {

/// Class encapsulating OpenGL shader program.
class Shader {
public:

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void bind();
    void unbind();

private:

    void initProgram(const std::string& vertexPath, const std::string& fragmentPath);
    void destroyProgram();

private:

    GLuint mProgramID;

};

GLuint loadShader(const std::string& path, GLenum shaderType);
std::string getContents(const std::string& path);
std::string getProgramLog(GLuint programID);
std::string getShaderLog(GLuint shaderID);

} // namespace snk

#endif
