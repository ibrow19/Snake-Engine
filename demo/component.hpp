#ifndef DEMO_COMPONENT_HEADER
#define DEMO_COMPONENT_HEADER

#include <snk/component/component.hpp>
#include <snk/node/node.hpp>
#include "identifiers.hpp"

class TestComponent : public snk::Component {
public:

    void reset() {}

    void init() {

        getOwner().addChild(getContext().nManager.createNode(node::Id::Test2));

    }

    void update(float delta) {

        getOwner().rotate(delta * -100.f);
        getOwner().translate(delta * mXSpeed, delta * mYSpeed);

    }

    void move(float xMove, float yMove) {
        
        mXSpeed = xMove * mMoveSpeed;
        mYSpeed = yMove * mMoveSpeed;

    }

private:

    float mMoveSpeed = 200.f;
    float mXSpeed = 0.f; 
    float mYSpeed = 0.f; 

};

class TestComponent2 : public snk::Component {

    void reset() {}

    void update(float delta) {

        getOwner().translate(delta * 20.f, 0.f);

    }

};

#endif
