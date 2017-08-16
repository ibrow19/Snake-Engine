#include <SDL2/SDL.h>
#include <snk/error/sdlexception.hpp>

namespace snk {

SDLException::SDLException() 
: SnakeException(std::string("SDL error: ") + SDL_GetError()) {}

} // namespace snk
