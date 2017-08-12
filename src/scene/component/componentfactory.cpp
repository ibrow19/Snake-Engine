#include <cassert>
#include <scene/component/component.hpp>
#include <scene/component/componentfactory.hpp>

namespace snk {

ComponentFactory::ComponentFactory(unsigned int componentCount) 
: mComponentTypes(componentCount) {}


void ComponentFactory::initComponent(ComponentId componentId,
                                     ComponentPointer& newComponent) {

    // ComponentManager should have carried out this checks.
    assert(componentId < mComponentTypes.size());

    if (!mComponentTypes[componentId].init) {

        throw SnakeException("Attempting to create component with unitialised type");

    }
    
    newComponent.setComponent(mComponentTypes[componentId].factory());

}


unsigned int ComponentFactory::getComponentCount() const {

    return mComponentTypes.size();

}

} // namespace snk
