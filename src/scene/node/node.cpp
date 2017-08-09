#include <cassert>
#include <scene/node/node.hpp>
#include <texturemanager.hpp>
#include <scene/component/componentmanager.hpp>
#include <scene/node/nodemanager.hpp>

namespace snk {

Node::Node()
: mDestroyed(false),
  mHasTexture(false),
  mDirty(true),  // Must be true initially to initialise world transform
  mLocalData({{0.f, 0.f}, 0.f, {1.f, 1.f}, {0.f, 0.f}}),
  mLocal(),
  mWorld(),
  mTextureId(0),
  mTManager(nullptr),
  mCManager(nullptr),
  mNManager(nullptr),
  //mParent(),
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
    mTManager = nullptr;
    mCManager = nullptr;
    mNManager = nullptr;
    //mParent = NodeHandle();
    mComponents.clear();
    mChildren.clear();

}


void Node::init(const NodeHandle& handle,
                TextureManager& tManager, 
                ComponentManager& cManager,
                NodeManager& nManager,  
                bool hasTexture, 
                TextureId textureId,
                const std::vector<ComponentId>& components) {

    assert (mTManager == nullptr);
    assert (mCManager == nullptr);
    assert (mNManager == nullptr);
    
    mHasTexture = hasTexture;
    mTextureId = textureId;

    mTManager = &tManager;
    mCManager = &cManager;
    mNManager = &nManager;

    // Add components.
    for (auto it = components.cbegin(); it != components.cend(); ++it) {

        // TODO: it may be useful to keep handle of node as member function.
        addComponent(*it, handle);

    }

    // Initialise componenets once all of them have been added.
    for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {

        mCManager->dereference(it->first, it->second).init();

    }

}


void Node::addChild(const NodeHandle& childHandle) {

    // Assert to check node is initialised.
    assert(mTManager != nullptr);
    mChildren.push_back(childHandle);
    //Node child& = mNManager.dereference(childHandle);
    //if (child.mParent.getCounter() != 0) {

    //    throw SnakeException("Cannot add child that already has a parent");

    //}
    //child.mParent = mHandle;

}


void Node::render() {

    assert(mTManager != nullptr);
    Transform t;
    render(t, false);

}


void Node::destroy() {

    assert(mTManager != nullptr);
    mDestroyed = true;
    for (auto it = mChildren.begin(); it != mChildren.end(); ++it) {

        mNManager->dereference(*it);

    }

    // TODO: Destroying marked nodes should be the last thing that happens. This gives
    //       destroyed components to use the node's state for actions upon destruction.
    // Mark components for destruction.
    for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {

        // mCManager.deregerence(it->first, it->second).destroy();

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


void Node::addComponent(ComponentId componentId, const NodeHandle& owner) {

    // TODO: this check could be quite costly and unnecessary.
    if (mComponents.find(componentId) != mComponents.end()) {

        throw SnakeException("A Node cannot have one than one of one type of commponent");

    }
    mComponents[componentId] = mCManager->createComponent(componentId, owner, *mNManager);

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
    for (auto it = mChildren.begin(); it != mChildren.end(); ++it) {

        mNManager->dereference(*it).render(mWorld, dirty);

    }

}

} // namespace snk
