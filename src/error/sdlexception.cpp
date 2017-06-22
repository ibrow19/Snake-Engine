#include <SDL2/SDL.h>
#include "error/sdlexception.hpp"

namespace snk {

SDLException::SDLException() 
: std::runtime_error(std::string("SDL error: ") + SDL_GetError()) {}

} // namespace snk