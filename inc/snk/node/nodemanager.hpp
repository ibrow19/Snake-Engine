#ifndef SNAKE_NODE_MANAGER_HEADER
#define SNAKE_NODE_MANAGER_HEADER

#include <snk/identifiers.hpp>
#include <snk/resource/resourcemanager.hpp>

namespace snk {

class Node;
class Component;
class ComponentManager;
class NodeFactory;

/// Stores all nodes in one place in addition to factories for game objects.
class NodeManager {
public:

    /// Initialise with how many different kind of nodes there will be.
    NodeManager(ComponentManager& cManager,
                NodeFactory& nFactory);

    /// Create a node of the specified type.
    NodeHandle createNode(NodeId nodeId);  

    Node& dereference(const NodeHandle& handle);
    const Node& dereference(const NodeHandle& handle) const;

    /// Destroy marked nodes.
    void destroyMarked();

private:

    ComponentManager& mCManager;
    NodeFactory& mNFactory;

    ResourceManager<Node, NodeTag> mNodes;

};

} // namespace snk

#endif
