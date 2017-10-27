#ifndef DEMO_INPUT_HANDLER_HEADER
#define DEMO_INPUT_HANDLER_HEADER

#include <snk/input/inputhandler.hpp>
#include "identifiers.hpp"
#include "ship.hpp"
#include "rotation.hpp"

class Input : public snk::InputHandler {

    void reset();
    void handleEvent(const SDL_Event& event, snk::CommandQueue& queue);

private:

    snk::Command rightCommand(snk::ComponentId id, bool right);
    snk::Command leftCommand(snk::ComponentId id, bool left);
    snk::Command boostCommand(bool boost);

};

#endif
