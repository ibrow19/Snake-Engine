#ifndef SNAKE_SCENE_HEADER
#define SNAKE_SCENE_HEADER

#include <identifiers.hpp>

namespace snk {

class Node;
class TextureManager;
class ComponentManager;
class NodeManager;
class ComponentFactory;
class NodeFactory;

class Scene {
public:

    Scene(NodeId rootId,
          TextureManager& tManager,
          ComponentFactory& cFactory,
          NodeFactory& nFactory);

    //void handleCommand(Command& command);
    void update(float delta);
    void render();

private:
    
    ComponentManager mCManager;
    NodeManager mNManager;

    NodeHandle mRootHandle;

};

} // namespace snk

#endif
