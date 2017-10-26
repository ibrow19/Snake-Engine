#ifndef SNAKE_NODE_FACTORY_HEADER
#define SNAKE_NODE_FACTORY_HEADER

#include <snk/identifiers.hpp>
#include <snk/node/nodedata.hpp>

namespace snk {

class Node;
class TextureManager;
class ComponentManager;
class NodeManager;

class NodeFactory {
public:

    NodeFactory(NodeId nodeCount);

    /// Register components and textures that make up a node.
    void registerNode(NodeId nodeId, const NodeData& nodeData);
    const NodeData& getNodeData(NodeId nodeId) const;

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
