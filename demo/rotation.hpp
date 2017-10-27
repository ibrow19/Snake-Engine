#ifndef DEMO_ROTATION_COMPONENT_HEADER
#define DEMO_ROTATION_COMPONENT_HEADER

#include <snk/component/component.hpp>
#include <snk/node/node.hpp>
#include "identifiers.hpp"

#define ROTATION_RATE 180.f

class RotationComponent : public snk::Component {
public:

    void reset();
    void init();
    void update(float delta);
    void setRight(bool right);
    void setLeft(bool left);

private:

    bool mRight;
    bool mLeft;

};

#endif
