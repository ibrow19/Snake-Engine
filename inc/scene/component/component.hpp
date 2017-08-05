#ifndef SNAKE_COMPONENT_HEADER
#define SNAKE_COMPONENT_HEADER

#include <resource.hpp>


namespace snk {

class Component : public Resource {
public:

    Component();

    void reset();
    
    // init is called when node using this component is initialised.
    virtual void init();

    virtual void update(float delta);

    //virtual void destroy();

protected:

    //NodeHandle parentHandle;

};

} // namespace snk

#endif
