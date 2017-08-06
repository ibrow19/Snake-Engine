#ifndef SNAKE_COMPONENT_HEADER
#define SNAKE_COMPONENT_HEADER

#include <handle.hpp>
#include <resource.hpp>

namespace snk {

class NodeTag;
typedef Handle<NodeTag> NodeHandle;

class Component : public Resource {
public:

    // TODO: initialise parent.
    Component();

    // init is called when node using this component is initialised.
    virtual void init();

    virtual void update(float delta);

protected:

    NodeHandle parentHandle;

};

} // namespace snk

#endif
