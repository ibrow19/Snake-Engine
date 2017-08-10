#include <scene/component/component.hpp>
#include <scene/component/componentmanager.hpp>
#include <scene/component/componentfactory.hpp>

namespace snk {

ComponentManager::ComponentManager(ComponentFactory& cFactory) 
: mCFactory(cFactory),
  mComponents(mCFactory.getComponentCount()) {}


ComponentHandle ComponentManager::createComponent(ComponentId componentId,
                                                  const NodeHandle& owner,
                                                  NodeManager& nManager) {

    if (componentId >= mComponents.size()) {

        throw SnakeException("Attempting to create component using Id that is greater than maximum Id");

    }
    
    ComponentHandle newHandle;
    ComponentPointer& newComponent = mComponents[componentId].create(newHandle);
    // TODO: dont need to use factory if component is from ResourceManager pool rather than new.
    mCFactory.initComponent(componentId, newComponent);
    newComponent.getComponent().init(nManager, owner);
    return newHandle;

}


Component& ComponentManager::dereference(ComponentId componentId, const ComponentHandle& handle) {

    if (componentId >= mComponents.size()) {

        throw SnakeException("Attempting to dereference component Id that is greater than maximum Id");

    }
    return mComponents[componentId].dereference(handle).getComponent();

}


const Component& ComponentManager::dereference(ComponentId componentId, const ComponentHandle& handle) const {

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