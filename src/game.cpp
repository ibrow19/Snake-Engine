#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "exception.hpp"
#include "game.hpp"


Game::Game() {

    init();

}


Game::~Game() {

    exit();

}


void Game::run() {

    // TODO: implement.
    printf("running...\n");

}



void Game::init() {

    printf("initialising...\n");

    if ((SDL_Init(SDL_INIT_VIDEO) < 0) ||
        (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))) {

        throw SDLInitException();

    }

}



/// Closes SDL subsystems used by the game.
void Game::exit() {

    printf("exiting...\n");

    IMG_Quit();
    SDL_Quit();

    printf("finished\n");
}
