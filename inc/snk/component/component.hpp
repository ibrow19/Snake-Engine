#ifndef SNAKE_COMPONENT_HEADER
#define SNAKE_COMPONENT_HEADER

#include <snk/identifiers.hpp>
#include <snk/resource/resource.hpp>
#include <snk/context.hpp>

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
    /// Initialise newly created component with owner and scene for fetching context.
    void init(Context& context, 
              const NodeHandle& owner);

    // init is called when node using this component is initialised.
    virtual void init();
    virtual void update(float delta);

protected:

    Context& getContext();
    Node& getOwner();

private:

    Context* mContext;
    NodeHandle mOwnerHandle;

};

} // namespace snk

#endif
