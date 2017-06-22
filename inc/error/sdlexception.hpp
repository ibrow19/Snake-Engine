#ifndef SNAKE_SDL_EXCEPTION_HEADER
#define SNAKE_SDL_EXCEPTION_HEADER

#include <stdexcept>

namespace snk {

class SDLException : public std::runtime_error {
public:

    SDLException();

};

} // namespace snk

#endif
