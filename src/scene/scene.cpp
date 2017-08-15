#include <error/snkexception.hpp>
#include <texturemanager.hpp>
#include <scene/component/componentfactory.hpp>
#include <scene/node/node.hpp>
#include <scene/node/nodefactory.hpp>
#include <scene/scene.hpp>

namespace snk {

Scene::Scene(NodeId rootId,
             TextureManager& tManager,
             std::unique_ptr<InputHandler> iHandler,
             ComponentFactory& cFactory,
             NodeFactory& nFactory)
: mIHandler(std::move(iHandler)),
  mCManager(cFactory),
  mNManager(tManager,
            mCManager,
            nFactory),
  mRootHandle(mNManager.createNode(rootId)) {}


void Scene::handleEvent(const SDL_Event& event) {

    assert(mIHandler != nullptr);
    mIHandler->handleEvent(event, mCQueue);

}


void Scene::update(float delta) {
    
    Command command;
    while (mCQueue.pollCommands(command)) {

        mCManager.handleCommand(command);

    }
    mCManager.update(delta);

}


void Scene::render() {

    assert(mRootHandle.getCounter() != 0);
    mNManager.dereference(mRootHandle).render();

};

} // namespace snk
