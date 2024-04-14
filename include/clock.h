#include "SFML/Graphics.hpp"
#include <functional>
#include <iostream>

#ifndef _CLOCK_
#define _CLOCK_

class Clock
{
private:
    float tick;
    float threshold;
    float initial_time;
    float time;
    float total_time;
    sf::Clock c;
    sf::Time dt;
    std::function<void()> delayed_function;

public:
    Clock(float t);
    void update();
    void update(float n);
    void restart(bool function_activation = true);
    void set_threshold(float t);
    float get_tick();
    float get_time();
    float get_total_time();
    float get_threshold();
    float get_initial_time();
    bool need_restart();
    void delay_a_function(std::function<void()> f);
    void reset();
};

#endif