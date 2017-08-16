#include <algorithm>
#include <functional>
#include <snk/error/snkexception.hpp>
#include <snk/texture/texturemanager.hpp>
#include <snk/component/componentmanager.hpp>
#include <snk/node/nodefactory.hpp>
#include <snk/node/node.hpp>

namespace snk {

NodeFactory::NodeFactory(unsigned int nodeCount)
: mNodeTypes(nodeCount) {}


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


const NodeData& NodeFactory::getNodeData(NodeId nodeId) const {

    if (nodeId >= mNodeTypes.size()) {

        throw SnakeException("Attempting to get node data with Id which is greater than maximum node Id");

    }

    const NodeType& nodeType = mNodeTypes[nodeId];
    if (!nodeType.init) {

        throw SnakeException("Attempting to get node data with unitialised type");
    
    }

    return nodeType.data;

}

} // namespace snk
