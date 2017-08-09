#ifndef SNAKE_COMPONENT_HEADER
#define SNAKE_COMPONENT_HEADER

#include <identifiers.hpp>
#include <resource.hpp>

namespace snk {

class Node;
class NodeManager;

class Component : public Resource {
public:

    // TODO: initialise owner.
    Component();
    virtual ~Component();

    // TODO: this function shouldn't be exposed.
    /// Initialise newly created component with owner and manager.
    void init(NodeManager& manager, const NodeHandle& owner);

    // init is called when node using this component is initialised.
    virtual void init();
    virtual void update(float delta);

protected:

    Node& getOwner();

protected:

    NodeManager* mNManager;
    NodeHandle mOwnerHandle;

};

} // namespace snk

#endif
