#ifndef DEMO_INPUT_HANDLER_HEADER
#define DEMO_INPUT_HANDLER_HEADER

#include <scene/input/inputhandler.hpp>
#include "identifiers.hpp"
#include "component.hpp"

class TestIHandler : public snk::InputHandler {

    void reset() {}

    snk::Command createMove(float xMove, float yMove) {

        auto move =
        [xMove, yMove](TestComponent& component) {

            component.move(xMove, yMove);

        };
        return snk::createCommand<TestComponent>(component::Id::Test1, move);

    }

    void handleEvent(const SDL_Event& event, snk::CommandQueue& queue) {

        if (event.type == SDL_KEYDOWN) {

            switch (event.key.keysym.sym) {

                case SDLK_UP:
                    queue.push(createMove(0.f, -1.f));
                    break;

                case SDLK_DOWN:
                    queue.push(createMove(0.f, 1.f)); 
                    break;

                case SDLK_RIGHT:
                    queue.push(createMove(1.f, 0.f)); 
                    break;

                case SDLK_LEFT:
                    queue.push(createMove(-1.f, 0.f)); 
                    break;

            }

        }

    }

};

#endif
