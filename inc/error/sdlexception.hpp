#ifndef SNAKE_SDL_EXCEPTION_HEADER
#define SNAKE_SDL_EXCEPTION_HEADER

#include <error/snkexception.hpp>

namespace snk {

class SDLException : public SnakeException {
public:

    SDLException();

};

} // namespace snk

#endif
