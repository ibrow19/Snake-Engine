#include <snk/texture/texturemanager.hpp>
#include <snk/component/componentfactory.hpp>
#include <snk/component/componentmanager.hpp>
#include <snk/node/nodefactory.hpp>
#include <snk/node/nodemanager.hpp>
#include <snk/node/node.hpp>
#include <snk/scene/scenemanager.hpp>

namespace snk {

SceneManager::SceneManager(unsigned int sceneCount,
                           TextureManager& tManager,
                           IHandlerFactory& iFactory,
                           ComponentFactory& cFactory,
                           NodeFactory& nFactory)
: mTManager(tManager),
  mIFactory(iFactory),
  mCFactory(cFactory),
  mNFactory(nFactory),
  mSceneTypes(sceneCount) {}


void SceneManager::registerScene(SceneId sceneId, const SceneData& data) {

    if (sceneId >= mSceneTypes.size()) {

        throw SnakeException("Attempting to initialise scene type Id which is greater than maximum scene Id");

    }

    if (mSceneTypes[sceneId].init) {

        throw SnakeException("Attempting to initialise already initialised scene type Id");

    }

    mSceneTypes[sceneId].init = true;
    mSceneTypes[sceneId].data = data;

}


void SceneManager::push(SceneId sceneId) {

    StackAction action({Push, sceneId});
    mActionQueue.push(action);

}

void SceneManager::pop() {

    StackAction action({Pop, 0});
    mActionQueue.push(action);

}


void SceneManager::replace(SceneId sceneId) {

    StackAction action({Replace, sceneId});
    mActionQueue.push(action);

}


void SceneManager::clear() {

    StackAction action({Clear, 0});
    mActionQueue.push(action);

}

void SceneManager::update(float delta) {

    if (!mSceneStack.empty()) {

        mSceneStack.back().update(delta);

    }

}


void SceneManager::handleActions() {

    // Handle any scene stack changes.
    StackAction action;
    while (pollActions(action)) {

        switch (action.actionId) {

            case Push:
                pushScene(action.sceneId);
                break;

            // TODO: potentially id check popped scene to prevent multiple pop actions popping an
            //       extra scene.
            case Pop:
                popScene();
                break;

            case Replace:
                replaceScene(action.sceneId);
                break;

            case Clear:
                clearStack();

        }

    }

}


void SceneManager::handleEvent(const SDL_Event& event) {

    if (!mSceneStack.empty()) {

        mSceneStack.back().handleEvent(event);

    }

}


/// Render all scenes starting from the bottom of the stack, drawing the active scene last.
void SceneManager::render() {

    for (auto it = mSceneStack.begin(); it != mSceneStack.end(); ++it) {

        it->render();

    }

}


bool SceneManager::pollActions(StackAction& action) {

    if (mActionQueue.empty()) {

        return false;

    }

    action = mActionQueue.front();
    mActionQueue.pop();
    return true;

}


void SceneManager::pushScene(SceneId sceneId) {

    if (sceneId >= mSceneTypes.size()) {

        throw SnakeException("Attempting to create scene with Id which is greater than maximum sceneId");

    }

    if (!mSceneTypes[sceneId].init) {

        throw SnakeException("Attempting to create unitialised scene type");

    }
    mSceneStack.emplace_back(mSceneTypes[sceneId].data.rootId,
                             mTManager,
                             mIFactory.createIHandler(mSceneTypes[sceneId].data.iHandlerId),
                             mCFactory,
                             mNFactory);

}


void SceneManager::popScene() {

    if (mSceneStack.empty()) {

        throw SnakeException("Cannot pop scene from empty stack");

    }
    mSceneStack.pop_back();

}


void SceneManager::replaceScene(SceneId sceneId) {

    popScene();
    pushScene(sceneId);

}


void SceneManager::clearStack() {

    mSceneStack.clear();

}

} // namespace snk
