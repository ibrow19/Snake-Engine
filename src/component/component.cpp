#include <snk/node/node.hpp>
#include <snk/node/nodemanager.hpp>
#include <snk/component/component.hpp>
#include <snk/component/componentmanager.hpp>

namespace snk {

Component::Component() 
: mCManager(nullptr),
  mNManager(nullptr),
  mOwnerHandle() {}

Component::~Component() {}

void Component::init(ComponentManager& cManager,
                     NodeManager& nManager, 
                     const NodeHandle& owner) {

    mCManager = &cManager;
    mNManager = &nManager;
    mOwnerHandle = owner;

}


// Default init and update functionality does nothing.
void Component::init() {}
void Component::update(float /* delta */) {}


Node& Component::getOwner() {

    assert(mCManager != nullptr);
    assert(mNManager != nullptr);
    return mNManager->dereference(mOwnerHandle);

}

} // namespace snk
