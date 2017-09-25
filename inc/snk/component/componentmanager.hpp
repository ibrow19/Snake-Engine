#ifndef SNAKE_COMPONENT_MANAGER_HEADER
#define SNAKE_COMPONENT_MANAGER_HEADER

#include <vector>
#include <snk/identifiers.hpp>
#include <snk/resource/resourcemanager.hpp>
#include <snk/component/componentpointer.hpp>

namespace snk {

class ComponentFactory;
class Command;
class Scene;

class ComponentManager {
public:

    ComponentManager(Scene& scene,
                     ComponentFactory& cFactory);

    ComponentHandle createComponent(ComponentId componentId,
                                    const NodeHandle& owner);

    Component& dereference(ComponentId componentId, const ComponentHandle& handle);
    const Component& dereference(ComponentId componentId, const ComponentHandle& handle) const;

    void handleCommand(Command& command);
    void update(float delta); 

private:
    
    Scene& mScene;
    ComponentFactory& mCFactory;

    // TODO: specialise ComponentPointer resourcemanager iterator to getComponent on dereference.
    //       to allow a user to more easily iterate through components of a certain type.
    // ResourceManager for for each component type.
    std::vector<ResourceManager<ComponentPointer, ComponentTag>> mComponents;

};

} // namespace snk

#endif
