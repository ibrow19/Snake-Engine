#include "rotation.hpp"

RotationComponent::RotationComponent()
: mRight(false),
  mLeft(false) {}


void RotationComponent::reset() {
    
    mRight = false;
    mLeft = false;

}


void RotationComponent::update(float delta) {

    if (mLeft && !mRight) {

        getOwner().rotate(-ROTATION_RATE * delta);

    } else if (mRight && !mLeft) {

        getOwner().rotate(ROTATION_RATE * delta);

    }

}


void RotationComponent::setRight(bool right) {

    mRight = right;

}


void RotationComponent::setLeft(bool left) {

    mLeft = left;

}
