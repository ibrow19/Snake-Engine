#include <cassert>
#include <snk/node/node.hpp>
#include <snk/texture/texturemanager.hpp>
#include <snk/component/componentmanager.hpp>
#include <snk/node/nodemanager.hpp>

namespace snk {

Node::Node()
: mDestroyed(false),
  mHasTexture(false),
  mDirty(true),  // Must be true initially to initialise world transform
  mTextureId(0),
  mLocalData({{0.f, 0.f}, 0.f, {1.f, 1.f}, {0.f, 0.f}}),
  mLocal(),
  mWorld(),
  mComponents(),
  mChildren() {}


void Node::reset() {

    mDestroyed = false;
    mHasTexture = false;
    mDirty = true;  // Must be true initially to initialise world transform
    mLocalData = Transform::TData({{0.f, 0.f}, 0.f, {1.f, 1.f}, {0.f, 0.f}});
    mLocal = Transform();
    mWorld = Transform();
    mTextureId = 0;
    mComponents.clear();
    mChildren.clear();

}


void Node::setTexture(TextureId textureId) {

    mHasTexture = true;
    mTextureId = textureId;

}


void Node::addChild(const NodeHandle& handle) {

    mChildren.push_back(handle);

}


void Node::addComponent(ComponentId componentId, const ComponentHandle& handle) {

    mComponents[componentId] = handle;

}


bool Node::hasComponent(ComponentId componentId) const {

    auto found = mComponents.find(componentId);
    if (found == mComponents.end()) {

        return false;

    }
    return true;

}


const ComponentHandle& Node::getComponent(ComponentId componentId) const {

    if (!hasComponent(componentId)) {

        throw SnakeException("Attempting to get component that node does not have");

    }
    return mComponents.at(componentId);

}


void Node::render(TextureManager& tManager, NodeManager& nManager) {

    Transform transform;
    render(tManager, nManager, transform, false);

}


void Node::destroy() {

    //mDestroyed = true;
    //for (auto it = mChildren.begin(); it != mChildren.end(); ++it) {

    //    mNManager->dereference(*it);

    //}

    //// TODO: Destroying marked nodes should be the last thing that happens. This gives
    ////       destroyed components to use the node's state for actions upon destruction.
    //// Mark components for destruction.
    //for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {

    //    // mCManager.dereference(it->first, it->second).destroy();

    //}

}


bool Node::isDestroyed() const {

    return mDestroyed;

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


void Node::render(TextureManager& tManager,
                  NodeManager& nManager,
                  const Transform& world, 
                  bool dirty) {

    if (mDirty) {

        mLocal = Transform(mLocalData);

    }
    dirty = dirty || mDirty;
    mDirty = false;
    if (dirty) {

        mWorld = world * mLocal;

    }
    if (mHasTexture) {

        Texture& texture = tManager.getTexture(mTextureId);
        texture.render(mWorld);

    }

    // Factor out origin translation for children.
    Transform originless(mWorld);
    originless.translate(mLocalData.origin);
    for (auto it = mChildren.begin(); it != mChildren.end(); ++it) {

        nManager.dereference(*it).render(tManager, nManager, originless, dirty);

    }

}

} // namespace snk
