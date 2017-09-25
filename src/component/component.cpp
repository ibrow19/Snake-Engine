#include <snk/node/node.hpp>
#include <snk/node/nodemanager.hpp>
#include <snk/component/component.hpp>
#include <snk/component/componentmanager.hpp>

namespace snk {

Component::Component() 
: mContext(nullptr),
  mOwnerHandle() {}


Component::~Component() {}


void Component::init(Context& context, const NodeHandle& owner) {

    mContext = &context;
    mOwnerHandle = owner;

}


// Default init and update functionality does nothing.
void Component::init() {}
void Component::update(float /* delta */) {}


Node& Component::getOwner() {

    assert(mContext != nullptr);
    return mContext->nManager.dereference(mOwnerHandle);

}


const NodeHandle& Component::getOwnerHandle() const {

    return mOwnerHandle;

}


bool Component::hasComponent(const NodeHandle& ownerHandle, ComponentId componentId) {

    assert(mContext != nullptr);
    return mContext->nManager.dereference(ownerHandle).hasComponent(componentId);

}


bool Component::hasComponent(ComponentId componentId) {

    return hasComponent(mOwnerHandle, componentId);

}


void Component::addChild(NodeId nodeId) {

    assert(mContext != nullptr);
    mContext->nManager.dereference(mOwnerHandle).addChild(mContext->nManager.createNode(nodeId));

}

} // namespace snk
