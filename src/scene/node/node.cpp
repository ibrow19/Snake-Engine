#include <cassert>
#include <scene/node/node.hpp>

namespace snk {

Node::Node()
: mParent(nullptr),
  mDestroyed(false),
  mDirty(true),  // Must be true initially to initialise world transform
  mLocal(),
  mWorld(),
  mLocalData({{0.f, 0.f}, 0.f, {1.f, 1.f}, {0.f, 0.f}}),
  mTManager(nullptr),
  mHasTexture(false),
  mTextureId(0) {}


void Node::reset() {

    mParent = nullptr;
    mDestroyed = false;
    mDirty = true;
    mLocal = Transform();
    mWorld = Transform();
    mLocalData = Transform::TData({{0.f, 0.f}, 0.f, {1.f, 1.f}, {0.f, 0.f}});
    mTManager = nullptr;
    mHasTexture = false;
    mTextureId = 0;
    mChildren.clear();

    // TODO: remove components.

}


void Node::init(TextureManager& tManager, bool hasTexture, TextureManager::Id textureId) {

    assert (mTManager == nullptr);
    mTManager = &tManager;
    mHasTexture = hasTexture;
    mTextureId = textureId;

}


void Node::addChild(Node& child) {

    assert(mTManager != nullptr);
    child.mParent = this;
    mChildren.push_back(&child);

}


void Node::render() {

    // TODO: use asserts over exceptions in more performance critical areas.
    assert(mTManager != nullptr);
    Transform t;
    render(t, false);

}


void Node::destroy() {

    assert(mTManager != nullptr);
    mDestroyed = true;
    for (Node* child : mChildren) {

        child->destroy();

    }

}


bool Node::isDestroyed() const {

    assert(mTManager != nullptr);
    return mDestroyed;

}


// Origin
const Point2f& Node::getOrigin() const {

    assert(mTManager != nullptr);
    return mLocalData.origin;

}


void Node::setOrigin(Point2f origin) {

    assert(mTManager != nullptr);
    setOrigin(origin.x, origin.y);

}


void Node::setOrigin(float x, float y) {

    assert(mTManager != nullptr);
    mLocalData.origin.x = x;
    mLocalData.origin.y = y;
    mDirty = true;

}

// Scale
const Vector2f& Node::getScale() const {

    assert(mTManager != nullptr);
    return mLocalData.scale;

}


void Node::setScale(float factor) {

    assert(mTManager != nullptr);
    setScale(factor, factor);

}


void Node::setScale(const Vector2f& factor) {

    assert(mTManager != nullptr);
    setScale(factor.x, factor.y);

}


void Node::setScale(float x, float y) {

    assert(mTManager != nullptr);
    mLocalData.scale.x = x;
    mLocalData.scale.y = y;
    mDirty = true;

}


void Node::scale(float factor) {

    assert(mTManager != nullptr);
    setScale(factor * mLocalData.scale.x, factor * mLocalData.scale.y);

}


void Node::scale(const Vector2f& factor) {

    assert(mTManager != nullptr);
    setScale(factor.x * mLocalData.scale.x, factor.y * mLocalData.scale.y);

}


void Node::scale(float x, float y) {

    assert(mTManager != nullptr);
    setScale(x * mLocalData.scale.x, y * mLocalData.scale.y);

}


// Rotate.
float Node::getRotation() const {

    assert(mTManager != nullptr);
    return mLocalData.angle;

}


void Node::setRotation(float angle) {

    assert(mTManager != nullptr);
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

    assert(mTManager != nullptr);
    setRotation(mLocalData.angle + angle);

}


// Translation.
const Vector2f& Node::getTranslation() const {

    assert(mTManager != nullptr);
    return mLocalData.translation;

}


void Node::setTranslation(const Vector2f& v) {

    assert(mTManager != nullptr);
    setTranslation(v.x, v.y);

}


void Node::setTranslation(float x, float y) {

    assert(mTManager != nullptr);
    mLocalData.translation.x = x;
    mLocalData.translation.y = y;
    mDirty = true;

}


void Node::translate(const Vector2f& v) {

    assert(mTManager != nullptr);
    setTranslation(v.x + mLocalData.translation.x, v.y + mLocalData.translation.y);

}


void Node::translate(float x, float y) {

    assert(mTManager != nullptr);
    setTranslation(x + mLocalData.translation.x, y + mLocalData.translation.y);

}


void Node::render(const Transform& world, bool dirty) {

    assert(mTManager != nullptr);
    if (mDirty) {

        mLocal = Transform(mLocalData);

    }
    dirty = dirty || mDirty;
    mDirty = false;
    if (dirty) {

        mWorld = world * mLocal;

    }
    if (mHasTexture) {

        Texture& texture = mTManager->getTexture(mTextureId);
        texture.render(mWorld);

    }
    for (Node* child : mChildren) {

        assert(child != nullptr);
        child->render(mWorld, dirty);

    }

}

} // namespace snk
