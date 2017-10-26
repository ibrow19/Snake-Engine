#include <cassert>
#include <snk/component/component.hpp>
#include <snk/component/componentfactory.hpp>

namespace snk {

ComponentFactory::ComponentFactory(ComponentId componentCount) 
: mComponentTypes(componentCount) {}


std::unique_ptr<Component> ComponentFactory::createComponent(ComponentId componentId) const {

    // ComponentManager should have carried out this checks.
    assert(componentId < mComponentTypes.size());

    if (!mComponentTypes[componentId].init) {

        throw SnakeException("Attempting to create component with unitialised type");

    }
    
    return mComponentTypes[componentId].factory();

}


ComponentId ComponentFactory::getComponentCount() const {

    return mComponentTypes.size();

}

} // namespace snk
