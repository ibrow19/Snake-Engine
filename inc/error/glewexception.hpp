#ifndef SNAKE_GLEW_EXCEPTION_HEADER
#define SNAKE_GLEW_EXCEPTION_HEADER

#include <GL/glew.h>
#include <GL/gl.h>
#include "error/snkexception.hpp"

namespace snk {

class GLEWException : public SnakeException {
public:

    GLEWException(GLenum error);

};

} // namespace snk

#endif
