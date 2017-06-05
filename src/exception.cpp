#include "exception.hpp"


SDLException::SDLException() 
: std::runtime_error(std::string("SDL error: ") + SDL_GetError()) {}
