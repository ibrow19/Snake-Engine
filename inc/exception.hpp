#include <stdexcept>
#include <SDL2/SDL.h>

class SDLException : public std::runtime_error {
public:

    SDLException();

};
