#include "exception.hpp"

namespace snk {

SDLException::SDLException() 
: std::runtime_error(std::string("SDL error: ") + SDL_GetError()) {}

} // namespace snk
