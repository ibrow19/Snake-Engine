#ifndef SNAKE_NODE_FACTORY_HEADER
#define SNAKE_NODE_FACTORY_HEADER

#include <identifiers.hpp>

namespace snk {

class Node;
class TextureManager;
class ComponentManager;
class NodeManager;

class NodeFactory {
public:

    struct NodeData {

        bool hasTexture = false;
        TextureId textureId;
        std::vector<ComponentId> components;

    };

public:

    NodeFactory(unsigned int nodeCount);

    /// Register components and textures that make up a node.
    void registerNode(NodeId nodeId, const NodeData& nodeData);
    void initNode(NodeId nodeId, 
                  Node& newNode,
                  const NodeHandle& newHandle,
                  TextureManager& tManager,
                  ComponentManager& cManager,
                  NodeManager& nManager) const;

private:

    struct NodeType {

        bool init = false;
        NodeData data;

    };

private:

    std::vector<NodeType> mNodeTypes;

};

} // namespace snk

#endif
