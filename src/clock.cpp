#include "clock.h"

// Clock is in milliseconds
Clock::Clock(float t)
{
    threshold = t;
    tick = 0;
    time = 0;
}

// Update the tick by adding the delta time together until it reaches the threshold
void Clock::update()
{
    dt = c.restart();
    time += dt.asMilliseconds();
    tick = time / threshold;
}

// Update the tick given a specific value
void Clock::update(float n)
{
    time = n;
    tick = time / threshold;
}

// Reset the tick, and time
void Clock::restart()
{
    tick = 0;
    time = 0;
}

// Return tick
float Clock::get_tick()
{
    return tick;
}

// Return total time
float Clock::get_time()
{
    return time;
}

// Return threshold
float Clock::get_threshold()
{
    return threshold;
}

// Return whether the time needs a restart or not
bool Clock::need_restart()
{
    return time >= threshold;
}
