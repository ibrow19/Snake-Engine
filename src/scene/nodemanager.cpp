#include <algorithm>
#include <functional>
#include <error/snkexception.hpp>
#include <scene/nodemanager.hpp>

namespace snk {

NodeManager::NodeManager(unsigned int nodeCount, 
                         TextureManager& tManager, 
                         ComponentManager& cManager) 
: mTManager(tManager),
  mCManager(cManager),
  mNodeTypes(nodeCount) {

    if (nodeCount == 0) {

        throw SnakeException("Node manager must manage at least one type of node");

    }

}


void NodeManager::registerNode(Id nodeId, const NodeData& nodeData) {

    if (nodeId >= mNodeTypes.size()) {

        throw SnakeException("Attempting to assign node type Id which is greater than maximum node Id");

    }

    if (mNodeTypes.at(nodeId).init) {

        throw SnakeException("Attempting to assign already assigned node type Id");

    }

    // TODO: possibly add validation of texture here, although invalid texturee Ids will
    //       get caught when a node of this type is initialised.

    // TODO: component validation.
   
    mNodeTypes.at(nodeId).init = true;
    mNodeTypes.at(nodeId).data = nodeData;

}


Node& NodeManager::createNode(Id nodeId) {

    if (nodeId >= mNodeTypes.size()) {

        throw SnakeException("Attempting to create node with Id which is greater than maximum node Id");

    }

    NodeType& nodeType = mNodeTypes.at(nodeId);
    if (!nodeType.init) {

        throw SnakeException("Attempting to create node with unitialised type");
    
    }

    Texture* texture = nullptr;
    if (nodeType.data.hasTexture) {

        texture = &(mTManager.getTexture(nodeType.data.textureId));

    }

    std::unique_ptr<Node> newNode(new Node(texture));
    Node& newRef = *(newNode.get());
    mNodes.push_back(std::move(newNode));
    return newRef;

}


void NodeManager::destroyMarked() {

    // Note: component cleanup is handled by component manager. 

    auto removeBegin = std::remove_if(mNodes.begin(), mNodes.end(),
                                      std::mem_fn(&Node::isDestroyed));

    mNodes.erase(removeBegin, mNodes.end());

}

} // namespace snk
