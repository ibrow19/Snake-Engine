#ifndef SNAKE_GL_EXCEPTION_HEADER
#define SNAKE_GL_EXCEPTION_HEADER

#include <GL/gl.h>
#include <GL/glu.h>
#include <error/snkexception.hpp>

namespace snk {

/// Exception to report openGL errors.
class GLException : public SnakeException {
public:

    /// Initialise with OpenGL error code.
    /// \param error OpenGL error code.
    GLException(GLenum error);

    /// Initialise with OpenGL error code.
    /// \param message additonal error information.
    /// \param error OpenGL error code.
    GLException(const std::string& message, GLenum error);

};

/// Check whether OpenGl error has occured. If it has, throw an exception.
void checkGLError();

/// Check whether OpenGl error has occured. If it has, throw an exception.
/// \param message additonal error information.
void checkGLError(const std::string& message);

} // namespace snk

#endif
