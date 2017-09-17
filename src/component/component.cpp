#include <snk/node/node.hpp>
#include <snk/node/nodemanager.hpp>
#include <snk/component/component.hpp>
#include <snk/component/componentmanager.hpp>

namespace snk {

Component::Component() 
: mContext(nullptr),
  mOwnerHandle() {}

Component::~Component() {}

void Component::init(Context& context,
                     const NodeHandle& owner) {

    mContext = &context;
    mOwnerHandle = owner;

}


// Default init and update functionality does nothing.
void Component::init() {}
void Component::update(float /* delta */) {}


Context& Component::getContext() {

    assert(mContext != nullptr);
    return *mContext;

}


Node& Component::getOwner() {

    return getContext().nManager.dereference(mOwnerHandle);

}

} // namespace snk
