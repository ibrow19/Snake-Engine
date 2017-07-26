#ifndef SNAKE_NODE_MANAGER_HEADER
#define SNAKE_NODE_MANAGER_HEADER

#include <texturemanager.hpp>
#include <scene/node.hpp>
#include <scene/componentmanager.hpp>

namespace snk {

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
    Node& createNode(Id nodeId);  

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

    // TODO: All managers need a way of storing references to resources in a contiguous
    // fashion that can cope with relocation from vector resizes. Unique_ptrs to the
    // resources can cope with relocation in the vector but resources are not
    // stored contiguously.
    std::vector<std::unique_ptr<Node>> mNodes;

};

} // namespace snk

#endif
