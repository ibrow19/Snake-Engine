#ifndef SNAKE_SCENE_MANAGER_HEADER
#define SNAKE_SCENE_MANAGER_HEADER

#include <snk/identifiers.hpp>
#include <snk/input/ihandlerfactory.hpp>
#include <snk/scene/scene.hpp>
#include <snk/scene/scenedata.hpp>

namespace snk {

/// Controls creation and management of scenes and delegates updates and events to them.
class SceneManager {
public:

    SceneManager(unsigned int sceneCount,
                 TextureManager& tManager,
                 IHandlerFactory& iFactory,
                 ComponentFactory& cFactory,
                 NodeFactory& nFactory);

    // TODO: more advanced scene initialisation (more than just one node).
    void registerScene(SceneId sceneId, const SceneData& data);

    /// Push a new active scene onto the stack.
    /// \param sceneId Id of the new active scene to push onto the stack.
    void push(SceneId sceneId);

    /// Pop the active scene from the stack.
    void pop();

    /// Replace the active scene with another.
    void replace(SceneId sceneId);

    /// Clear all scenes from the stack.
    void clear();

    /// Update the active scene. Other scenes in the stack are not updated and remain suspended.
    /// \param delta update step.
    void update(float delta);

    /// Handle queued stack actions.
    void handleActions();

    /// Handle event in the active scene.
    /// \param event the event to handle out.
    void handleEvent(const SDL_Event& event);

    /// Render all scenes starting from the bottom of the stack, drawing the active scene last.
    void render();

private:

    /// Actions that can be carried out on the stack.
    enum ActionId {

        Push,
        Pop,
        Replace,
        Clear,

    };

private:

    struct StackAction {

        ActionId actionId;
        SceneId sceneId; 

    };

    struct SceneType {

        bool init = false;
        SceneData data;

    };

private:

    /// Poll stack actions that need to be carried out.
    bool pollActions(StackAction& action);
    void pushScene(SceneId sceneId);
    void popScene();
    void replaceScene(SceneId sceneId);
    void clearStack();

private:

    TextureManager& mTManager;
    IHandlerFactory& mIFactory;
    ComponentFactory& mCFactory;
    NodeFactory& mNFactory;

    std::vector<SceneType> mSceneTypes;

    std::queue<StackAction> mActionQueue;
    std::vector<Scene> mSceneStack;  

};

} // namespace snk

#endif
