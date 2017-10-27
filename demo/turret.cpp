#include "turret.hpp"

void TurretComponent::reset() {}


void TurretComponent::init() {

    getOwner().setOrigin(15.f, 50.f);
    getOwner().translate(0.f, 30.f);

}
