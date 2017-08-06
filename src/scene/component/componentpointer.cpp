#include <cassert>
#include <scene/component/componentpointer.hpp>

namespace snk {

ComponentPointer::ComponentPointer() 
: mComponent(nullptr) {}


void ComponentPointer::reset() {

    mComponent->reset();

}


void ComponentPointer::setComponent(const Factory& factory) {

    assert(mComponent == nullptr);
    mComponent = factory();

}


Component& ComponentPointer::getComponent() {

    return *mComponent;

}


const Component& ComponentPointer::getComponent() const {

    return *mComponent;

}

} // namespace snk
