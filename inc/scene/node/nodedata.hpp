#ifndef SNAKE_NODE_DATA_HEADER
#define SNAKE_NODE_DATA_HEADER

namespace snk {

struct NodeData {

    bool hasTexture = false;
    TextureId textureId;
    std::vector<ComponentId> components;

};

} // namespace snk

#endif
