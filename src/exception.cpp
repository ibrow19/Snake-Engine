#include "exception.hpp"


SDLException::SDLException() 
: std::runtime_error("SDL error: " + std::string(SDL_GetError())) {}
