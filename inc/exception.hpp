#ifndef SNAKE_EXCEPTION_HEADER
#define SNAKE_EXCEPTION_HEADER

#include <stdexcept>
#include <SDL2/SDL.h>

namespace snk {

class SDLException : public std::runtime_error {
public:

    SDLException();

};

} // namespace snk

#endif
