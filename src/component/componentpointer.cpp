#include <cassert>
#include <snk/component/componentpointer.hpp>

namespace snk {

ComponentPointer::ComponentPointer() 
: mComponent(nullptr) {}


void ComponentPointer::reset() {

    // TODO: this is currently unnecessary as new components are reassigned using factory on
    // creation.
    mComponent->reset();

}


void ComponentPointer::setComponent(std::unique_ptr<Component> component) {

    assert(mComponent == nullptr);
    mComponent = std::move(component);

}


Component& ComponentPointer::getComponent() {

    return *mComponent; 

}


const Component& ComponentPointer::getComponent() const {

    return *mComponent;

}

} // namespace snk
