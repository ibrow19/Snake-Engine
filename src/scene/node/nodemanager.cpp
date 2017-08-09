#include <algorithm>
#include <functional>
#include <error/snkexception.hpp>
#include <texturemanager.hpp>
#include <scene/component/componentmanager.hpp>
#include <scene/node/node.hpp>
#include <scene/node/nodemanager.hpp>

namespace snk {

NodeManager::NodeManager(unsigned int nodeCount, 
                         TextureManager& tManager, 
                         ComponentManager& cManager) 
: mTManager(tManager),
  mCManager(cManager),
  mNodeTypes(nodeCount) {}


void NodeManager::registerNode(NodeId nodeId, const NodeData& nodeData) {

    if (nodeId >= mNodeTypes.size()) {

        throw SnakeException("Attempting to initialise node type Id which is greater than maximum node Id");

    }

    if (mNodeTypes[nodeId].init) {

        throw SnakeException("Attempting to initialise already initialised node type Id");

    }

    // TODO: possibly add validation of texture here, although invalid texturee Ids will
    //       get caught when a node of this type is initialised.

    // TODO: component validation.
   
    mNodeTypes[nodeId].init = true;
    mNodeTypes[nodeId].data = nodeData;

}


NodeHandle NodeManager::createNode(NodeId nodeId) {

    if (nodeId >= mNodeTypes.size()) {

        throw SnakeException("Attempting to create node with Id which is greater than maximum node Id");

    }

    NodeType& nodeType = mNodeTypes[nodeId];
    if (!nodeType.init) {

        throw SnakeException("Attempting to create node with unitialised type");
    
    }

    NodeHandle newHandle;
    Node& newNode = mNodes.create(newHandle);
    newNode.init(newHandle,
                 mTManager, 
                 mCManager,
                 *this,
                 nodeType.data.hasTexture, 
                 nodeType.data.textureId,
                 nodeType.data.components);
    return newHandle;

}


Node& NodeManager::dereference(const NodeHandle& handle) {

    return mNodes.dereference(handle);

}


const Node& NodeManager::dereference(const NodeHandle& handle) const {

    return mNodes.dereference(handle);

}


void NodeManager::destroyMarked() {

    // TODO: reconsider how node destruction is carried out. 
    //       Possibly add destruction method to iterator so handle not strictly required for
    //       destruction.

    // Note: component cleanup is handled by component manager. 

    //auto removeBegin = std::remove_if(mNodes.begin(), mNodes.end(),
    //                                  std::mem_fn(&Node::isDestroyed));

    //mNodes.erase(removeBegin, mNodes.end());

}

} // namespace snk
