#include <SDL2/SDL.h>


class Game {
public:

    Game();
    ~Game();

    /// set game settings.
    //void settings...

    /// Runs the game until it is finsished
    void run();

private:

    /// Initialises SDL subsystems necessary for the game.
    void initSDL();

    /// Closes SDL subsystems used by the game.
    void exitSDL();

    void createWin();
    void createRen();

    void handleEvents();
    void update();
    void render();

private:

    //char* mTitle;

    int mWidth;
    int mHeight;

    Uint32 mWinFlags;
    Uint32 mRenFlags;

    SDL_Window* mWin;
    SDL_Renderer* mRen; 

};
