#ifndef DEMO_SHIP_COMPONENT_HEADER
#define DEMO_SHIP_COMPONENT_HEADER

#include <snk/component/component.hpp>
#include <snk/node/node.hpp>
#include "identifiers.hpp"

#define SHIP_ACCELERATION 1000.f
#define SHIP_DECELERATION 500.f
#define SHIP_MAX_SPEED 1000.f

class ShipComponent : public snk::Component {
public:

    ShipComponent();
    void reset();
    void init();
    void update(float delta);
    void setBoost(bool boost);

private:

    float mSpeed;
    bool mBoost;

};

#endif
