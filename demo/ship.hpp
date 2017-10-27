#ifndef DEMO_SHIP_COMPONENT_HEADER
#define DEMO_SHIP_COMPONENT_HEADER

#include <snk/component/component.hpp>
#include <snk/node/node.hpp>
#include "identifiers.hpp"

#define SHIP_ACCELERATION 10.f
#define SHIP_DECELERATION 5.f
#define SHIP_MAX_SPEED 10.f

class ShipComponent : public snk::Component {
public:

    void reset();
    void init();
    void update(float delta);
    void setBoost(bool boost);

private:

    float mSpeed;
    bool mBoost;

};

#endif
