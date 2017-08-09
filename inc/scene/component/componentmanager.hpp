#ifndef SNAKE_COMPONENT_MANAGER_HEADER
#define SNAKE_COMPONENT_MANAGER_HEADER

#include <vector>
#include <identifiers.hpp>
#include <resourcemanager.hpp>
#include <error/snkexception.hpp>
#include <scene/component/componentpointer.hpp>

namespace snk {

class ComponentManager {
public:

    ComponentManager(unsigned int componentCount);

    template<typename T>
    void registerComponent(ComponentId componentId);

    ComponentHandle createComponent(ComponentId componentId,
                                    const NodeHandle& owner,
                                    NodeManager& nManager);

    Component& dereference(ComponentId componentId, const ComponentHandle& handle);
    const Component& dereference(ComponentId componentId, const ComponentHandle& handle) const;

    void update(float delta); 

private:

    struct ComponentType {

        bool init = false;
        ComponentPointer::Factory factory;

    };

private:

    // Factories for creating components.
    std::vector<ComponentType> mComponentTypes;

    // TODO: specialise ComponentPointer resourcemanager iterator to getComponent on dereference.
    //       to allow a user to more easily iterate through components of a certain type.
    // ResourceManager for for each component type.
    std::vector<ResourceManager<ComponentPointer, ComponentTag>> mComponents;

};


template<typename T>
void ComponentManager::registerComponent(ComponentId componentId) {

    if (componentId >= mComponentTypes.size()) {

        throw SnakeException("Attempting to initialise component type Id which is greater than maximum component Id");

    }

    if (mComponentTypes[componentId].init) {

        throw SnakeException("Attempting to initialise already initialised component type Id");

    }

    mComponentTypes[componentId].init = true;
    mComponentTypes[componentId].factory = 
    []() {

        return std::unique_ptr<T>(new T());

    };

}

} // namespace snk

#endif
