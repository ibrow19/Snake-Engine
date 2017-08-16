#ifndef SNAKE_COMPONENT_HEADER
#define SNAKE_COMPONENT_HEADER

#include <snk/identifiers.hpp>
#include <snk/resource/resource.hpp>

namespace snk {

class Node;
class NodeManager;
class ComponentManager;

class Component : public Resource {
public:

    // TODO: initialise owner.
    Component();
    virtual ~Component();

    // TODO: this function shouldn't be exposed.
    /// Initialise newly created component with owner and manager.
    void init(ComponentManager& cManager, 
              NodeManager& nManager, 
              const NodeHandle& owner);

    // init is called when node using this component is initialised.
    virtual void init();
    virtual void update(float delta);

protected:

    Node& getOwner();

protected:

    // TODO: make functions to interact with these rather than giving users direct access to them.
    // TODO: might not need component manager ref.
    ComponentManager* mCManager;
    NodeManager* mNManager;

private:

    NodeHandle mOwnerHandle;

};

} // namespace snk

#endif
