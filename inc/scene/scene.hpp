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

    Scene(TextureManager& tManager,
          ComponentFactory& cFactory,
          NodeFactory& nFactory);

    //void handleCommand(Command& command);
    void update(float delta);
    void render();

    void setRoot(NodeId rootId);

private:
    
    NodeHandle mRootHandle;

    ComponentManager mCManager;
    NodeManager mNManager;

};

} // namespace snk

#endif
