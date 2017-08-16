#include <SDL2/SDL.h>
#include <snk/error/glewexception.hpp>

namespace snk {

GLEWException::GLEWException(GLenum error) 
: SnakeException(std::string("GLEW error: ") + 
                 reinterpret_cast<const char*>(glewGetErrorString(error))) {}

} // namespace snk
