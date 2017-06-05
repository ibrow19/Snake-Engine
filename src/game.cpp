#include <cassert>
#include <cstdio>
#include <SDL2/SDL_image.h>
#include "exception.hpp"
#include "game.hpp"


Game::Game() 
: //mTitle(nullptr) 
  mWidth(1240),
  mHeight(720),
  mWinFlags(SDL_WINDOW_SHOWN),  // Default window options.
  mRenFlags(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),  // Default renderer options.
  mWin(nullptr),
  mRen(nullptr),
  running(false) {

    initSDL();

}


Game::~Game() {

    SDL_DestroyRenderer(mRen);
    SDL_DestroyWindow(mWin);
    exitSDL();

}


void Game::run() {

    // Create window and render.
    createWin();
    createRen();

    // TODO: implement.
    printf("running...\n");

    running = true;
    while (running) {

        handleEvents();
        update();
        render();

    }

    // Destroy window and renderer.
    SDL_DestroyRenderer(mRen);
    SDL_DestroyWindow(mWin);

}


void Game::initSDL() {

    printf("initialising...\n");

    if ((SDL_Init(SDL_INIT_VIDEO) < 0) ||
        (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))) {

        throw SDLException();

    }

}


void Game::exitSDL() {

    printf("exiting...\n");

    IMG_Quit();
    SDL_Quit();

    printf("finished\n");

}


// TODO: add window settings customisation.
void Game::createWin() {

    if (mWin != nullptr) {

        SDL_DestroyWindow(mWin);

    }

    // TODO: add title customisation.
    mWin = SDL_CreateWindow("Game",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            mWidth,
                            mHeight,
                            mWinFlags);

    if (mWin == nullptr) {

        throw SDLException();

    }

}


// TODO: add renderer settings customisation.
void Game::createRen() {

    if (mRen != nullptr) {

        SDL_DestroyRenderer(mRen);

    }

    mRen = SDL_CreateRenderer(mWin, -1, mRenFlags);

    if (mRen == nullptr) {

        throw SDLException();

    }
}


void Game::handleEvents() {

    SDL_Event event;

    while (running && SDL_PollEvent(&event)) {

        running = event.type != SDL_QUIT;

    }

}


void Game::update() {

    // TODO: implement.

}


void Game::render() {

    // TODO: implement.

}


void Game::setVSync(bool active) {

    if (active) {

        mRenFlags |= SDL_RENDERER_PRESENTVSYNC;
        assert(mRenFlags & SDL_RENDERER_PRESENTVSYNC);

    } else {

        mRenFlags &= ~SDL_RENDERER_PRESENTVSYNC;
        assert(!(mRenFlags & SDL_RENDERER_PRESENTVSYNC));

    }

}
