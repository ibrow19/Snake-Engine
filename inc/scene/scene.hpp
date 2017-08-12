#ifndef SNAKE_SCENE_HEADER
#define SNAKE_SCENE_HEADER

#include <SDL.h>
#include <memory>
#include <identifiers.hpp>
#include <scene/input/inputhandler.hpp>

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
          std::unique_ptr<InputHandler> iHandler,
          TextureManager& tManager,
          ComponentFactory& cFactory,
          NodeFactory& nFactory);

    void handleEvent(const SDL_Event& event);
    void update(float delta);
    void render();

private:

    std::unique_ptr<InputHandler> mIHandler;
    
    ComponentManager mCManager;
    NodeManager mNManager;

    NodeHandle mRootHandle;

    CommandQueue mCQueue;

};

} // namespace snk

#endif
