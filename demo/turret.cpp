#include "turret.hpp"

void TurretComponent::reset() {}


void TurretComponent::init() {

    getOwner().setClip(clip::Ship::Turret);
    getOwner().setOrigin(15.f, 50.f);
    getOwner().translate(0.f, 30.f);

}
