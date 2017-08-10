#ifndef SNAKE_COMPONENT_MANAGER_HEADER
#define SNAKE_COMPONENT_MANAGER_HEADER

#include <vector>
#include <identifiers.hpp>
#include <resourcemanager.hpp>
#include <error/snkexception.hpp>
#include <scene/component/componentpointer.hpp>

namespace snk {

class ComponentFactory;

class ComponentManager {
public:

    ComponentManager(ComponentFactory& cFactory);

    ComponentHandle createComponent(ComponentId componentId,
                                    const NodeHandle& owner,
                                    NodeManager& nManager);

    Component& dereference(ComponentId componentId, const ComponentHandle& handle);
    const Component& dereference(ComponentId componentId, const ComponentHandle& handle) const;

    void update(float delta); 

private:
    
    ComponentFactory& mCFactory;

    // TODO: specialise ComponentPointer resourcemanager iterator to getComponent on dereference.
    //       to allow a user to more easily iterate through components of a certain type.
    // ResourceManager for for each component type.
    std::vector<ResourceManager<ComponentPointer, ComponentTag>> mComponents;

};

} // namespace snk

#endif
