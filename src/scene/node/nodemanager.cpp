#include <algorithm>
#include <functional>
#include <error/snkexception.hpp>
#include <texturemanager.hpp>
#include <scene/component/componentmanager.hpp>
#include <scene/node/node.hpp>
#include <scene/node/nodemanager.hpp>
#include <scene/node/nodefactory.hpp>

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
    mNFactory.initNode(nodeId, newNode, newHandle, mTManager, mCManager, *this);
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
