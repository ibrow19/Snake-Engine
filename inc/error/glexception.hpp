#ifndef SNAKE_GL_EXCEPTION_HEADER
#define SNAKE_GL_EXCEPTION_HEADER

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdexcept>

namespace snk {

/// Exception to report openGL errors.
class GLException : public std::runtime_error {
public:

    /// Initialise with OpenGL error code.
    /// \param error OpenGL error code.
    GLException(GLenum error);

};

/// Check whether OpenGl error has occured. If it has, throw an exception.
void checkGLError();

} // namespace snk

#endif
