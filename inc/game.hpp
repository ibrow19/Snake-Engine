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
    void init();

    /// Closes SDL subsystems used by the game.
    void exit();

};
