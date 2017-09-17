#ifndef SNAKE_GAME_HEADER
#define SNAKE_GAME_HEADER

#include <string>
#include <SDL.h>
#include <snk/identifiers.hpp>
#include <snk/texture/texturemanager.hpp>
#include <snk/input/ihandlerfactory.hpp>
#include <snk/component/componentfactory.hpp>
#include <snk/node/nodefactory.hpp>
#include <snk/scene/scenemanager.hpp>

namespace snk {

// Class to run and manage a game.
class Game {
public:

    Game(unsigned int textureCount,
         unsigned int iHandlerCount,
         unsigned int componentCount,
         unsigned int nodeCount,
         unsigned int sceneCount);

    ~Game();

    /// Runs the game until it is finished
    void run();

    // Options configuration.

    /// Set the title used by the game window.
    /// \param title The new title to use.
    void setTitle(const std::string& title);

    /// Set the game window size.
    /// \param x Height of the window in pixels.
    /// \param y Width of the window in pixels.
    void setWinSize(int x, int y);

    /// Set whether the window is in full screen mode.
    /// \param full Whether the window should be full screen.
    void setFullScreen(bool full);

    /// Set whether vsync is used (Renderer uses vsync by default).
    /// \param vsync Whether vsync should be used.
    void setVSync(bool vsync);

    void setTexturePath(const std::string& texturePath);

    void registerTexture(TextureId textureId, const std::string& path);
    template<typename T>
    void registerIHandler(IHandlerId iHandlerId);
    template<typename T>
    void registerComponent(ComponentId componentId);
    void registerNode(NodeId nodeId, const NodeData& data);
    void registerScene(SceneId sceneId, const SceneData& data);
    void setInitialScene(SceneId sceneId);

private:

    /// Initialises SDL subsystems necessary for the game.
    void initSDL() const;

    /// Closes SDL subsystems used by the game.
    void exitSDL() const;

    /// Create and initialise window with current settings.
    void createWin();

    /// Destroy window.
    void destroyWin();

    /// Handle queued window events in the game world.
    void handleEvents();

    /// Update the game world based on how much time has passed.
    /// \param delta The time to update the game world with.
    void update(float delta);

    /// Draw the current state of the game world.
    void render();

private:

    /// Title for game window.
    std::string mTitle;

    /// Width of game window.
    int mWidth;

    /// Height of game window.
    int mHeight;

    /// Flags to use for window creation.
    Uint32 mWinFlags;

    /// Pointer to window displaying game.
    SDL_Window* mWin;

    /// OpenGL context.
    SDL_GLContext mContext;

    /// Whether the game is currently running.
    bool mRunning;

    /// Whether vsync should be used when rendering.
    bool mVsync;

    /// The maximum delta acceptable for an update.
    /// used to avoid large timesteps creating errors in logic.
    float mMaxDelta;

    TextureManager mTManager;
    IHandlerFactory mIFactory;
    ComponentFactory mCFactory;
    NodeFactory mNFactory;
    SceneManager mSManager;


};


template<typename T>
void Game::registerIHandler(IHandlerId iHandlerId) {

    mIFactory.registerIHandler<T>(iHandlerId);

}


template<typename T>
void Game::registerComponent(ComponentId componentId) {

    mCFactory.registerComponent<T>(componentId);

}

} // namespace snk

#endif
