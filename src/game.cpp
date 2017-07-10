#include <cassert>
#include <cstdio>
#include <iostream>
#include "error/glewexception.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include "error/sdlexception.hpp"
#include "error/glexception.hpp"
#include "shader/basic.hpp"
#include "timer.hpp"
#include "game.hpp"

#include "texture.hpp"

namespace snk {

Game::Game() 
: mTitle(""),
  mWidth(1240),
  mHeight(720),
  mWinFlags(SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN),  // Default window options.
  mWin(nullptr),
  mContext(nullptr),
  mRunning(false),
  mVsync(true) {

    initSDL();

}


Game::~Game() {

    destroyWin();
    exitSDL();

}


void Game::run() {

    // Create window.
    createWin();

    Timer timer;
    timer.start();

    // Shader and texture for rendering test.
    BasicShader s(mWidth, mHeight);
    Texture t(s, "texture.png");

    printf("running...\n");

    mRunning = true;
    while (mRunning) {

        // Handle queued events.
        handleEvents();

        // Get time past since last update and restart timer.
        float delta = timer.getTime();
        timer.start();

        // Update game world with time passed since last update.
        update(delta);

        // Draw the game world.
        //render();

        // Test rendering.
        glClear(GL_COLOR_BUFFER_BIT);
        t.render();
        SDL_GL_SwapWindow(mWin);

        // Check errors once per loop.
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {

            throw GLException("Error detected in main loop", error);

        }

    }
    
    // Destroy window.
    destroyWin();

}


void Game::initSDL() const {

    printf("initialising SDL...\n");

    bool success = true;

    int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG; 

    // Initialise subsystems.
    if ((SDL_Init(SDL_INIT_VIDEO) != 0) ||
        !(IMG_Init(imageFlags) & imageFlags)) {

        success = false;     

    } else {

        // Set OpenGl version as 3.2 core.
        // TODO: possibly define version numbers somewhere.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        // set core context.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    }

    // Upon failure destroy potentially half initialised subsystems.
    if (!success) {

        exitSDL();
        throw SDLException();

    }

}


void Game::exitSDL() const {

    printf("exiting...\n");

    IMG_Quit();
    SDL_Quit();

    printf("finished\n");

}


// initialisation.
void Game::createWin() {

    bool success = true;

    if (mWin != nullptr) {

        destroyWin();

    }

    mWin = SDL_CreateWindow(mTitle.c_str(),
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            mWidth,
                            mHeight,
                            mWinFlags);

    if (mWin == nullptr) {

        success = false;

    } else {

        mContext = SDL_GL_CreateContext(mWin);
        if (mContext == nullptr) {

            success = false;
            
        } else if (mVsync &&
                   SDL_GL_SetSwapInterval(1) != 0) {

            success = false;

        } else {

            glewExperimental = GL_TRUE;
            GLenum error = glewInit();

            // Reset gl error flag caused by some glew versions.
            glGetError();

            if (error != GLEW_OK) {

                destroyWin();
                throw GLEWException(error);

            }

        }

    }

    // Upon failure throw exception.
    if (!success) {

        destroyWin();
        throw SDLException();

    // Upon success initialise the window clear color.
    } else {

        glClearColor(1.f, 1.f, 1.f, 1.f);

    }

}


void Game::destroyWin() {

    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWin);

}


void Game::handleEvents() {

    SDL_Event event;
    while (mRunning && SDL_PollEvent(&event)) {

        mRunning = event.type != SDL_QUIT;

    }

}


void Game::update(float /*delta*/) {

    // TODO: implement.

}


void Game::render() {

    glClear(GL_COLOR_BUFFER_BIT);


    SDL_GL_SwapWindow(mWin);

}


void Game::setTitle(const std::string& title) {

    mTitle = title;

}


void Game::setWinSize(int x, int y) {

    mWidth = x;
    mHeight = y;

}


void Game::setFullScreen(bool full) {

    if (full) {

        mWinFlags |= SDL_WINDOW_FULLSCREEN;
        assert(mWinFlags & SDL_WINDOW_FULLSCREEN);

    } else {

        mWinFlags &= ~SDL_WINDOW_FULLSCREEN;
        assert(!(mWinFlags & SDL_WINDOW_FULLSCREEN));

    }

}


void Game::setVSync(bool vsync) {

    mVsync = vsync;

}

} // namespace snk
