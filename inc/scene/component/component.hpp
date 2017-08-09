#ifndef SNAKE_COMPONENT_HEADER
#define SNAKE_COMPONENT_HEADER

#include <identifiers.hpp>
#include <resource.hpp>

namespace snk {

class Component : public Resource {
public:

    // TODO: initialise owner.
    Component();

    // TODO: this function shouldn't be exposed.
    void setOwner(const NodeHandle& handle);

    // init is called when node using this component is initialised.
    virtual void init();
    virtual void update(float delta);

protected:

    //NodeManager mNManager;
    NodeHandle mOwnerHandle;

};

} // namespace snk

#endif
