#include <cassert>
#include <scene/node.hpp>

namespace snk {

Node::Node(Texture* texture)
: mParent(nullptr),
  mDirty(true),  // Must be true initially to initialise world transform
  mLocal(),
  mWorld(),
  mLocalData({{0.f, 0.f}, 0.f, {1.f, 1.f}, {0.f, 0.f}}),
  mTexture(texture) {}


void Node::addChild(Node& child) {

    child.mParent = this;
    mChildren.push_back(&child);

}


void Node::render() {

    Transform t;
    render(t, false);

}


// Origin
const Point2f& Node::getOrigin() const {

    return mLocalData.origin;

}


void Node::setOrigin(Point2f origin) {

    setOrigin(origin.x, origin.y);

}


void Node::setOrigin(float x, float y) {

    mLocalData.origin.x = x;
    mLocalData.origin.y = y;
    mDirty = true;

}

// Scale
const Vector2f& Node::getScale() const {

    return mLocalData.scale;

}


void Node::setScale(float factor) {

    setScale(factor, factor);

}


void Node::setScale(const Vector2f& factor) {

    setScale(factor.x, factor.y);

}


void Node::setScale(float x, float y) {

    mLocalData.scale.x = x;
    mLocalData.scale.y = y;
    mDirty = true;

}


void Node::scale(float factor) {

    setScale(factor * mLocalData.scale.x, factor * mLocalData.scale.y);

}


void Node::scale(const Vector2f& factor) {

    setScale(factor.x * mLocalData.scale.x, factor.y * mLocalData.scale.y);

}


void Node::scale(float x, float y) {

    setScale(x * mLocalData.scale.x, y * mLocalData.scale.y);

}


// Rotate.
float Node::getRotation() const {

    return mLocalData.angle;

}


void Node::setRotation(float angle) {

    // Calculate angle modulo 360.
    while (angle >= 360.f) {

        angle -= 360.f;

    }
    while (angle < 0.f) {

        angle += 360.f;

    }
    mLocalData.angle = angle;
    mDirty = true;

}


void Node::rotate(float angle) {

    setRotation(mLocalData.angle + angle);

}


// Translation.
const Vector2f& Node::getTranslation() const {

    return mLocalData.translation;

}


void Node::setTranslation(const Vector2f& v) {

    setTranslation(v.x, v.y);

}


void Node::setTranslation(float x, float y) {

    mLocalData.translation.x = x;
    mLocalData.translation.y = y;
    mDirty = true;

}


void Node::translate(const Vector2f& v) {

    setTranslation(v.x + mLocalData.translation.x, v.y + mLocalData.translation.y);

}


void Node::translate(float x, float y) {

    setTranslation(x + mLocalData.translation.x, y + mLocalData.translation.y);

}


void Node::render(const Transform& world, bool dirty) {

    if (mDirty) {

        mLocal = Transform(mLocalData);

    }
    dirty = dirty || mDirty;
    mDirty = false;
    if (dirty) {

        mWorld = world * mLocal;

    }
    if (mTexture != nullptr) {

        mTexture->render(mWorld);

    }
    for (Node* child : mChildren) {

        assert(child != nullptr);
        child->render(mWorld, dirty);

    }

}

} // namespace snk
