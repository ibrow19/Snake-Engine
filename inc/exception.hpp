#include <stdexcept>
#include <SDL2/SDL.h>

class SDLInitException : public std::runtime_error {
public:

    SDLInitException();

};
