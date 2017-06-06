#include "timer.hpp"


Timer::Timer()
: mStartTime(0),
  mPauseTime(0),
  mStarted(false),
  mPaused(false) {}


void Timer::start() {

    mStartTime = SDL_GetTicks();
    mPauseTime = 0;
    mStarted = true;
    mPaused = false;

}


void Timer::stop() {

    mStartTime = 0;
    mPauseTime = 0;
    mStarted = false;
    mPaused = false;

}


void Timer::pause() {

    if (mStarted && !mPaused) {

        mPauseTime = SDL_GetTicks();;
        mPaused = true;

    }

}


void Timer::unpause() {

    if (mStarted && mPaused) {

        // Increment start time my the time passed while paused to adjust
        // it to take into account the pause time.
        Uint32 currentTime = SDL_GetTicks();
        mStartTime += (currentTime - mPauseTime);
        mPauseTime = 0;
        mPaused = false;

    }

}


Uint32 Timer::getTime() const {

    if (!mStarted) {

        return 0;

    } else if (mPaused) {

        return mPauseTime - mStartTime;

    } else {

        Uint32 currentTime = SDL_GetTicks();
        return currentTime - mStartTime;

    }

}
