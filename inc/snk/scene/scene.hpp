#ifndef SNAKE_SCENE_HEADER
#define SNAKE_SCENE_HEADER

#include <SDL.h>
#include <memory>
#include <snk/identifiers.hpp>
#include <snk/input/inputhandler.hpp>
#include <snk/component/componentmanager.hpp>
#include <snk/node/nodemanager.hpp>
#include <snk/context.hpp>

namespace snk {

class Node;
class TextureManager;
class ComponentFactory;
class NodeFactory;

class Scene {
public:

    Scene(NodeId rootId,
          TextureManager& tManager,
          std::unique_ptr<InputHandler> iHandler,
          ComponentFactory& cFactory,
          NodeFactory& nFactory);

    void handleEvent(const SDL_Event& event);
    void update(float delta);
    void render();

    Context& getContext();

private:

    TextureManager& mTManager;
    std::unique_ptr<InputHandler> mIHandler;
    ComponentManager mCManager;
    NodeManager mNManager;

    Context mContext;

    NodeHandle mRootHandle;

    CommandQueue mCQueue;

};

} // namespace snk

#endif
