#include "clock.h"

// Clock is in milliseconds
Clock::Clock(float t)
{
    threshold = t;
    initial_time = t;
    tick = 0;
    time = 0;
    total_time = 0;
}

// Update the tick by adding the delta time together until it reaches the threshold
void Clock::update()
{
    dt = c.restart();
    time += dt.asMilliseconds();
    total_time += dt.asSeconds();
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
    c.restart();

    if (delayed_function)
    {
        delayed_function();
    }
    delayed_function = nullptr;
}

// Set the threshold
void Clock::set_threshold(float t)
{
    threshold = t;
}

// Return tick from a range 0 - 1
float Clock::get_tick()
{
    return tick;
}

// Return time as milliseconds
float Clock::get_time()
{
    return time;
}

// Return total time as seconds
float Clock::get_total_time()
{
    return total_time;
}

// Return threshold
float Clock::get_threshold()
{
    return threshold;
}

// Return initial time
float Clock::get_initial_time()
{
    return initial_time;
}

// Return whether the time needs a restart or not
bool Clock::need_restart()
{
    return time >= threshold;
}

void Clock::delay_a_function(std::function<void()> f)
{
    delayed_function = f;
}
