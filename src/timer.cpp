#include <timer.hpp>

namespace snk {

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


float Timer::getTime() const {

    Uint32 result = 0;
    if (mPaused) {

        result = mPauseTime - mStartTime;

    } else if (mStarted) {

        Uint32 currentTime = SDL_GetTicks();
        result = currentTime - mStartTime;

    }

    // return result in seconds.
    return result / 1000.f;

}

} // namespace snk
