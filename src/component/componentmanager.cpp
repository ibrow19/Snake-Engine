#include <snk/component/component.hpp>
#include <snk/component/componentmanager.hpp>
#include <snk/component/componentfactory.hpp>
#include <snk/input/command.hpp>

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
    newComponent.setComponent(mCFactory.createComponent(componentId));
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


void ComponentManager::handleCommand(Command& command) {

    if (command.getId() >= mComponents.size()) {

        throw SnakeException("Command with component Id out of bounds");

    }
    ResourceManager<ComponentPointer, ComponentTag>& targets = mComponents[command.getId()];
    for (auto it = targets.begin(); it != targets.end(); ++it) {

        command.execute(it->getComponent());

    }

}


void ComponentManager::update(float delta) {

    for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {

        for (auto cit = it->begin(); cit != it->end(); ++cit) {

            cit->getComponent().update(delta);

        }

    }

}

} // namespace snk
