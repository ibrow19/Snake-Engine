#include <algorithm>
#include <functional>
#include <snk/error/snkexception.hpp>
#include <snk/texture/texturemanager.hpp>
#include <snk/component/componentmanager.hpp>
#include <snk/node/node.hpp>
#include <snk/node/nodemanager.hpp>
#include <snk/node/nodefactory.hpp>

namespace snk {

NodeManager::NodeManager(TextureManager& tManager, 
                         ComponentManager& cManager,
                         NodeFactory& nFactory)
: mTManager(tManager),
  mCManager(cManager),
  mNFactory(nFactory) {}


NodeHandle NodeManager::createNode(NodeId nodeId) {

    NodeHandle newHandle;
    Node& newNode = mNodes.create(newHandle);
    const NodeData& data = mNFactory.getNodeData(nodeId);
    newNode.init(newHandle,
                 mTManager, 
                 mCManager,
                 *this,
                 data);
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
