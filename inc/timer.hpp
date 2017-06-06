#include <SDL2/SDL.h>


// Timer to record time passed using SDL.
class Timer {
public:

    Timer();

    /// Start the timer. If the timer is already started then it is restarted.
    void start();

    /// Stop the timer.
    void stop();

    /// Pause the timer at the current recorded time. Has no effect if called
    /// when the timer is not started or is already paused.
    void pause();

    /// Resume the timer if if it is paused. Has no effect if called when
    /// the timer is not paused.
    void unpause();

    /// Get the current time recorded by the timer.
    /// \return the time currently recorded by the timer in seconds.
    float getTime() const;

private:

    /// The time in milliseconds since the timer was started (measured from when the SDL was initialised).
    Uint32 mStartTime;

    /// The time at which the timer was paused.
    Uint32 mPauseTime;
    
    /// Whether the timer has been started.
    bool mStarted;

    /// Whether the program is paused.
    bool mPaused;
    
};
