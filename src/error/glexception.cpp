#include <snk/error/glexception.hpp>

namespace snk {

GLException::GLException(GLenum error) 
: SnakeException(std::string("OpenGL error: ") +
                 reinterpret_cast<const char*>(gluErrorString(error))) {}

GLException::GLException(const std::string& message, GLenum error) 
: SnakeException(message +
                 "\nOpenGL error: " + 
                 reinterpret_cast<const char*>(gluErrorString(error))) {}


void checkGLError() {

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {

        throw GLException(error);

    }

}

void checkGLError(const std::string& message) {

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {

        throw GLException(message, error);

    }

}

} // namespace snk
