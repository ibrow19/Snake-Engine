#include <SDL2/SDL.h>


// Class to run and manage a game.
class Game {
public:

    Game();
    ~Game();

    /// set game settings.
    //void settings...

    /// Runs the game until it is finsished
    void run();

    // Options configuration.

    /// Set whether vsync is used (used by default).
    /// \param val whether vsync should be used.
    void setVSync(bool active);

private:

    /// Initialises SDL subsystems necessary for the game.
    void initSDL() const;

    /// Closes SDL subsystems used by the game.
    void exitSDL() const;

    /// Create window with current settings.
    void createWin();

    /// Create renderer for game's window using current settings.
    void createRen();

    void handleEvents();
    void update(float deltaTime);
    void render();

private:

    //char* mTitle;

    int mWidth;
    int mHeight;

    Uint32 mWinFlags;
    Uint32 mRenFlags;

    SDL_Window* mWin;
    SDL_Renderer* mRen; 

    // Whether the game is currently running.
    bool mRunning;

};
