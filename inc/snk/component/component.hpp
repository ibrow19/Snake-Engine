#ifndef SNAKE_COMPONENT_HEADER
#define SNAKE_COMPONENT_HEADER

#include <cassert>
#include <snk/identifiers.hpp>
#include <snk/context.hpp>
#include <snk/error/snkexception.hpp>
#include <snk/resource/resource.hpp>
#include <snk/node/nodemanager.hpp>
#include <snk/component/componentmanager.hpp>

namespace snk {

class Node;

class Component : public Resource {
public:

    Component();
    virtual ~Component();

    // TODO: this function shouldn't be exposed.
    /// Initialise newly created component with owner and scene for fetching context.
    void init(Context& context, const NodeHandle& owner);

    // init is called when node using this component is initialised.
    virtual void init();
    virtual void update(float delta);

// Functions giving components relevant access to systems from the context.
protected:

    // TODO: remove and replace with functions giving components only enough access to do what they need.
    Node& getOwner();

    const NodeHandle& getOwnerHandle() const;

    void addChild(NodeId nodeId);  

    bool hasComponent(const NodeHandle& ownerHandle, ComponentId componentId);
    bool hasComponent(ComponentId componentId);

    template<typename T>
    T& getComponent(const NodeHandle& ownerHandle, ComponentId componentId);
    template<typename T>
    const T& getComponent(const NodeHandle& ownerHandle, ComponentId componentId) const;

    template<typename T>
    T& getComponent(ComponentId componentId);
    template<typename T>
    const T& getComponent(ComponentId componentId) const;

private:

    Context* mContext;
    NodeHandle mOwnerHandle;

};


template<typename T>
T& Component::getComponent(const NodeHandle& ownerHandle, ComponentId componentId) {

    assert(mContext != nullptr);
    const ComponentHandle& handle = mContext->nManager.dereference(ownerHandle);
    Component& component = mContext->cManager.dereference(componentId, handle);
    T* target = dynamic_cast<T*>(&component);
    if (target == nullptr) {

        throw SnakeException("Using wrong type for component dereference");

    }
    return *target; 

}


template<typename T>
const T& Component::getComponent(const NodeHandle& ownerHandle, ComponentId componentId) const {

    assert(mContext != nullptr);
    const ComponentHandle& handle = mContext->nManager.dereference(ownerHandle);
    const Component& component = mContext->cManager.dereference(componentId, handle);
    T* target = dynamic_cast<const T*>(&component);
    if (target == nullptr) {

        throw SnakeException("Using wrong type for component dereference");

    }
    return *target; 

}


template<typename T>
T& Component::getComponent(ComponentId componentId) {

    return getComponent<T>(componentId, mOwnerHandle);

}


template<typename T>
const T& Component::getComponent(ComponentId componentId) const {

    return getComponent<T>(componentId, mOwnerHandle);

}

} // namespace snk

#endif
