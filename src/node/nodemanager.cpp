#include <algorithm>
#include <functional>
#include <snk/error/snkexception.hpp>
#include <snk/texture/texturemanager.hpp>
#include <snk/component/componentmanager.hpp>
#include <snk/node/node.hpp>
#include <snk/node/nodemanager.hpp>
#include <snk/node/nodefactory.hpp>

namespace snk {

NodeManager::NodeManager(ComponentManager& cManager,
                         NodeFactory& nFactory)
: mCManager(cManager),
  mNFactory(nFactory) {}


// TODO: might be nicer to pass componentmanager to this function rather than have as member.
NodeHandle NodeManager::createNode(NodeId nodeId) {

    NodeHandle newHandle;
    Node& newNode = mNodes.create(newHandle);
    const NodeData& data = mNFactory.getNodeData(nodeId);
    if (data.hasTexture) {

        newNode.setTexture(data.textureId);

    }
    for (auto it = data.components.begin(); it != data.components.end(); ++it) {

        newNode.addComponent(*it, mCManager.createComponent(*it, newHandle));

    }
    for (auto it = data.components.begin(); it != data.components.end(); ++it) {

        mCManager.dereference(*it, newNode.getComponent(*it)).init();

    }
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
