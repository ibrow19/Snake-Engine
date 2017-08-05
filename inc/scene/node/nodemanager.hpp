#ifndef SNAKE_NODE_MANAGER_HEADER
#define SNAKE_NODE_MANAGER_HEADER

#include <texturemanager.hpp>
#include <scene/node/node.hpp>
#include <scene/component/componentmanager.hpp>

namespace snk {

struct NodeTag {};
typedef Handle<NodeTag> NodeHandle; 

/// Stores all nodes in one place in addition to factories for game objects.
//template<typename ... types>
class NodeManager {
public:

    typedef unsigned int Id;

public:

    struct NodeData {

        bool hasTexture = false;
        TextureManager::Id textureId;
        std::vector<ComponentManager::Id> componentIds;

    };

public:

    /// Initialise with how many different kind of nodes there will be.
    NodeManager(unsigned int nodeCount, 
                TextureManager& tManager, 
                ComponentManager& cManager);

    /// Register components and textures that make up a node.
    void registerNode(Id nodeId, const NodeData& nodeData);

    /// Create a node of the specified type.
    NodeHandle createNode(Id nodeId);  

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
