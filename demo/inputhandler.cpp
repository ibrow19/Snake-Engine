#include "inputhandler.hpp"

void Input::reset() {}


void Input::handleEvent(const SDL_Event& event, snk::CommandQueue& queue) {

    if (event.type == SDL_KEYDOWN) {

        switch (event.key.keysym.sym) {

            case SDLK_w:
                queue.push(boostCommand(true));
                break;

            case SDLK_a:
                queue.push(leftCommand(component::Id::ShipRotation, true));
                break;

            case SDLK_d:
                queue.push(rightCommand(component::Id::ShipRotation, true));
                break;

            case SDLK_LEFT:
                queue.push(leftCommand(component::Id::TurretRotation, true));
                break;

            case SDLK_RIGHT:
                queue.push(rightCommand(component::Id::TurretRotation, true));
                break;

        }

    } else if (event.type == SDL_KEYUP) {

        switch (event.key.keysym.sym) {

            case SDLK_w:
                queue.push(boostCommand(false));
                break;

            case SDLK_a:
                queue.push(leftCommand(component::Id::ShipRotation, false));
                break;

            case SDLK_d:
                queue.push(rightCommand(component::Id::ShipRotation, false));
                break;

            case SDLK_LEFT:
                queue.push(leftCommand(component::Id::TurretRotation, false));
                break;

            case SDLK_RIGHT:
                queue.push(rightCommand(component::Id::TurretRotation, false));
                break;

        }

    }

}


snk::Command Input::rightCommand(snk::ComponentId id, bool right) {

    auto c =
    [right](RotationComponent& r) {

        r.setRight(right);

    };
    return snk::createCommand<RotationComponent>(id, c);

}


snk::Command Input::leftCommand(snk::ComponentId id, bool left) {

    auto c =
    [left](RotationComponent& r) {

        r.setLeft(left);

    };
    return snk::createCommand<RotationComponent>(id, c);

}


snk::Command Input::boostCommand(bool boost) {

    auto c =
    [boost](ShipComponent& ship) {

        ship.setBoost(boost);

    };
    return snk::createCommand<ShipComponent>(component::Id::Ship, c);

}
