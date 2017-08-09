#ifndef SNAKE_NODE_MANAGER_HEADER
#define SNAKE_NODE_MANAGER_HEADER

#include <identifiers.hpp>

namespace snk {

class TextureManager;
class ComponentManager;
class Component;
class Node;

/// Stores all nodes in one place in addition to factories for game objects.
class NodeManager {
public:

    struct NodeData {

        bool hasTexture = false;
        TextureId textureId;
        std::vector<ComponentId> components;

    };

public:

    /// Initialise with how many different kind of nodes there will be.
    NodeManager(unsigned int nodeCount, 
                TextureManager& tManager, 
                ComponentManager& cManager);

    /// Register components and textures that make up a node.
    void registerNode(NodeId nodeId, const NodeData& nodeData);

    /// Create a node of the specified type.
    NodeHandle createNode(NodeId nodeId);  

    Node& dereference(const NodeHandle& handle);
    const Node& dereference(const NodeHandle& handle) const;

    /// Destroy marked nodes.
    void destroyMarked();

private:

    struct NodeType {

        bool init = false;
        NodeData data;

    };

private:

    TextureManager& mTManager;
    ComponentManager& mCManager;

    std::vector<NodeType> mNodeTypes;

    ResourceManager<Node, NodeTag> mNodes;

};

} // namespace snk

#endif
