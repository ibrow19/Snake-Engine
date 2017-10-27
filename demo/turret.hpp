#ifndef DEMO_TURRET_COMPONENT_HEADER
#define DEMO_TURRET_COMPONENT_HEADER

#include <snk/component/component.hpp>
#include <snk/node/node.hpp>
#include "identifiers.hpp"

class TurretComponent : public snk::Component {
public:

    void reset();
    void init();

};

#endif
