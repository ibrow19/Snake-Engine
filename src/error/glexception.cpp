#include "error/glexception.hpp"

namespace snk {

GLException::GLException(GLenum error) 
: std::runtime_error(std::string("OpenGL error: ") + 
                     reinterpret_cast<const char*>(gluErrorString(error))) {}

void checkGLError() {

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {

        throw GLException(error);

    }

}

} // namespace snk
