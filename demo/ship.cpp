#include "ship.hpp"

ShipComponent::ShipComponent()
: mSpeed(0.f),
  mBoost(false) {}


void ShipComponent::reset() {

    mSpeed = 0.f;
    mBoost = false;
    
}


void ShipComponent::init() {

    getOwner().setClip(clip::Ship::Body);
    getOwner().setOrigin(40.f, 50.f);
    getOwner().setTranslation(600.f, 400.f);
    addChild(node::Id::Turret);

}


void ShipComponent::update(float delta) {

    // Accelerate if boosting.
    if (mBoost) {

        mSpeed += SHIP_ACCELERATION * delta;
        if (mSpeed > SHIP_MAX_SPEED) {

            mSpeed = SHIP_MAX_SPEED;

        }

    }

    // Update position based on speed and rotation.
    snk::Transform r;
    r.rotate(getOwner().getRotation());
    snk::Vector2f velocity(0.f, -mSpeed * delta);
    velocity = r * velocity;
    getOwner().translate(velocity);

    // Decelerate.
    mSpeed -= SHIP_DECELERATION * delta;
    if (mSpeed < 0.f) {

        mSpeed = 0.f;

    }

}


void ShipComponent::setBoost(bool boost) {

    mBoost = boost;

}
