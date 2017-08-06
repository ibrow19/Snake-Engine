#include <scene/component/componentmanager.hpp>

namespace snk {

ComponentManager::ComponentManager(unsigned int componentCount) 
: mComponentTypes(componentCount),
  mComponents(componentCount) {}


ComponentHandle ComponentManager::createComponent(Id componentId) {

    if (componentId >= mComponents.size()) {

        throw SnakeException("Attempting to create component using Id that is greater than maximum Id");

    }

    if (!mComponentTypes[componentId].init) {

        throw SnakeException("Attempting to create component with unitialised type");

    }
    
    ComponentHandle newHandle;
    ComponentPointer& newComponent = mComponents[componentId].create(newHandle);
    newComponent.setComponent(mComponentTypes[componentId].factory);
    return newHandle;

}


Component& ComponentManager::dereference(Id componentId, const ComponentHandle& handle) {

    if (componentId >= mComponents.size()) {

        throw SnakeException("Attempting to dereference component Id that is greater than maximum Id");

    }
    return mComponents[componentId].dereference(handle).getComponent();

}


const Component& ComponentManager::dereference(Id componentId, const ComponentHandle& handle) const {

    if (componentId >= mComponents.size()) {

     
        throw SnakeException("Attempting to dereference component Id that is greater than maximum Id");

    }
    return mComponents[componentId].dereference(handle).getComponent();

}


void ComponentManager::update(float delta) {

    for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {

        for (auto cit = it->begin(); cit != it->end(); ++cit) {

            cit->getComponent().update(delta);

        }

    }

}

} // namespace snk
