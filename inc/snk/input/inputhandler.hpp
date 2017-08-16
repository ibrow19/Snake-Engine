#ifndef SNAKE_INPUT_HANDLER_HEADER
#define SNAKE_INPUT_HANDLER_HEADER

#include <SDL.h>
#include <vector>
#include <memory>
#include <snk/identifiers.hpp>
#include <snk/error/snkexception.hpp>
#include <snk/input/commandqueue.hpp>

namespace snk {

class InputHandler {
public:

    virtual ~InputHandler() {}

    virtual void handleEvent(const SDL_Event& event, CommandQueue& queue) = 0;

};

} // namespace snk

#endif
