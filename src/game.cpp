#include <cassert>
#include <iostream>
#include <snk/error/glewexception.hpp>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <snk/error/sdlexception.hpp>
#include <snk/error/glexception.hpp>
#include <snk/shader/basic.hpp>
#include <snk/node/node.hpp>
#include <snk/timer.hpp>
#include <snk/game.hpp>

namespace snk {

Game::Game(unsigned int textureCount,
           unsigned int iHandlerCount,
           unsigned int componentCount,
           unsigned int nodeCount,
           unsigned int sceneCount)
: mTitle(""),
  mWidth(1240),
  mHeight(720),
  mWinFlags(SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN),  // Default window options.
  mWin(nullptr),
  mContext(nullptr),
  mRunning(false),
  mVsync(true),
  mMaxDelta(1.f/30.f),
  mTManager(textureCount, "res/texture"),
  mIFactory(iHandlerCount),
  mCFactory(componentCount),
  mNFactory(nodeCount),
  mSManager(sceneCount, mTManager, mIFactory, mCFactory, mNFactory) {

    initSDL();

}


Game::~Game() {

    destroyWin();
    exitSDL();

}


void Game::run() {

    std::cout << "running.." << std::endl;

    // Create window and GL context.
    createWin();
    
    // Create shader to use for rendering.
    BasicShader shader(mWidth, mHeight);
    mTManager.setShader(shader);

    Timer timer;
    timer.start();

    // TODO: fixed gameloop.
    mRunning = true;
    while (mRunning) {

        // Handle queued events.
        handleEvents();

        // Get time past since last update and restart timer.
        float delta = timer.getTime();
        timer.start();


        // Update game world with time passed since last update.
        // Fixed update: Update in steps no largerthan max delta to avoid errors in logic.
        while (delta > mMaxDelta) {

            update(mMaxDelta);
            delta -= mMaxDelta;
            
        }
        update(delta);

        // Draw the game world.
        render();

        // Check errors once per loop.
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {

            throw GLException("Error detected in main loop", error);

        }

    }
    
    // Destroy window.
    destroyWin();

    // TODO: clear textures from textureManager as they no longer have a valid shader.

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


void Game::setTexturePath(const std::string& texturePath) {

    mTManager.setDefaultPath(texturePath);

}


void Game::registerTexture(TextureId textureId, const std::string& path) {

    mTManager.registerTexture(textureId, path);

}


void Game::registerNode(NodeId nodeId, const NodeData& data) {

    mNFactory.registerNode(nodeId, data);

}


void Game::registerScene(SceneId sceneId, const SceneData& data) {

    mSManager.registerScene(sceneId, data);

}


void Game::setInitialScene(SceneId sceneId) {

    mSManager.clear();
    mSManager.push(sceneId);
    mSManager.handleActions();

}


void Game::initSDL() const {

    std::cout << "initialising SDL.." << std::endl;

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

    std::cout << "exiting.." << std::endl;

    IMG_Quit();
    SDL_Quit();

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
        if (event.type != SDL_QUIT) {

            mSManager.handleEvent(event);

        }

    }

}


void Game::update(float delta) {

    mSManager.update(delta);
    mSManager.handleActions();

}


void Game::render() {

    glClear(GL_COLOR_BUFFER_BIT);
    
    mSManager.render();

    SDL_GL_SwapWindow(mWin);

}

} // namespace snk
