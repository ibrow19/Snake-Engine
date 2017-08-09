#include <scene/node/node.hpp>
#include <scene/node/nodemanager.hpp>
#include <scene/component/component.hpp>

namespace snk {

Component::Component() 
: mNManager(nullptr),
  mOwnerHandle() {}

Component::~Component() {}

void Component::init(NodeManager& manager, const NodeHandle& owner) {

    mNManager = &manager;
    mOwnerHandle = owner;

}


// Default init and update functionality does nothing.
void Component::init() {}
void Component::update(float /* delta */) {}


Node& Component::getOwner() {

    assert(mNManager != nullptr);
    return mNManager->dereference(mOwnerHandle);

}

} // namespace snk
