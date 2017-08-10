#include <algorithm>
#include <functional>
#include <error/snkexception.hpp>
#include <texturemanager.hpp>
#include <scene/component/componentmanager.hpp>
#include <scene/node/nodefactory.hpp>
#include <scene/node/node.hpp>

namespace snk {

NodeFactory::NodeFactory(unsigned int nodeCount, 
                         TextureManager& tManager, 
                         ComponentManager& cManager) 
: mTManager(tManager),
  mCManager(cManager),
  mNodeTypes(nodeCount) {}


void NodeFactory::registerNode(NodeId nodeId, const NodeData& nodeData) {

    if (nodeId >= mNodeTypes.size()) {

        throw SnakeException("Attempting to initialise node type Id which is greater than maximum node Id");

    }

    if (mNodeTypes[nodeId].init) {

        throw SnakeException("Attempting to initialise already initialised node type Id");

    }
    
    // TODO: Could be more efficient to validate textures and components validation.
    //       so that validation is not required every time a node is created.
   
    mNodeTypes[nodeId].init = true;
    mNodeTypes[nodeId].data = nodeData;

    std::vector<ComponentId>& components = mNodeTypes[nodeId].data.components;

    // Remove duplicate components.
    std::sort(components.begin(), components.end());
    auto last = std::unique(components.begin(), components.end());
    components.erase(last, components.end());

}


void NodeFactory::initNode(NodeId nodeId, 
                           Node& newNode,
                           const NodeHandle& newHandle,
                           NodeManager& nManager) const {

    if (nodeId >= mNodeTypes.size()) {

        throw SnakeException("Attempting to create node with Id which is greater than maximum node Id");

    }

    const NodeType& nodeType = mNodeTypes[nodeId];
    if (!nodeType.init) {

        throw SnakeException("Attempting to create node with unitialised type");
    
    }

    newNode.init(newHandle,
                 mTManager, 
                 mCManager,
                 nManager,
                 nodeType.data.hasTexture, 
                 nodeType.data.textureId,
                 nodeType.data.components);

}

} // namespace snk
