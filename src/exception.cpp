#include "exception.hpp"


SDLInitException::SDLInitException() 
: std::runtime_error("Failed to initialise SDL. SDL error: " + std::string(SDL_GetError())) {}
