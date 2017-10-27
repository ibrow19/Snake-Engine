#include "ship.hpp"

void ShipComponent::reset() {}


void ShipComponent::init() {

    mSpeed = 0.f;
    mBoost = false;
    getOwner().setOrigin(40.f, 50.f);
    getOwner().translate(600.f, 400.f);
    addChild(node::Id::Turret);

}


void ShipComponent::update(float delta) {

    if (mBoost) {

        mSpeed += SHIP_ACCELERATION * delta;
        if (mSpeed > SHIP_MAX_SPEED) {

            mSpeed = SHIP_MAX_SPEED;

        }

    }

    snk::Transform r;
    r.rotate(getOwner().getRotation());
    snk::Vector2f velocity(0.f, -mSpeed);
    velocity = r * velocity;
    getOwner().translate(velocity);

    mSpeed -= SHIP_DECELERATION * delta;
    if (mSpeed < 0.f) {

        mSpeed = 0.f;

    }

}


void ShipComponent::setBoost(bool boost) {

    mBoost = boost;

}
