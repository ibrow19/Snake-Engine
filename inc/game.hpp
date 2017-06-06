#include <string>
#include <SDL2/SDL.h>


// Class to run and manage a game.
class Game {
public:

    Game();
    ~Game();

    /// Runs the game until it is finsished
    void run();

    // Options configuration.

    /// Set the title used by the game window.
    /// \param title the new title to use.
    void setTitle(const std::string& title);

    /// Set whether vsync is used (Renderer uses vsync by default).
    /// \param vsync whether vsync should be used.
    void setVSync(bool vsync);

private:

    /// Initialises SDL subsystems necessary for the game.
    void initSDL() const;

    /// Closes SDL subsystems used by the game.
    void exitSDL() const;

    /// Create window with current settings.
    void createWin();

    /// Create renderer for game's window using current settings.
    void createRen();

    /// Handle queued window events in the game world.
    void handleEvents();

    /// Update the game world based on how much time has passed.
    /// \patam deltaTime the time to update the game world with.
    void update(float deltaTime);

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

    /// Flags to use for renderer creation.
    Uint32 mRenFlags;

    /// Pointer to window displaying game.
    SDL_Window* mWin;

    /// Pointer to renderer for drawing game.
    SDL_Renderer* mRen; 

    /// Whether the game is currently running.
    bool mRunning;

};
