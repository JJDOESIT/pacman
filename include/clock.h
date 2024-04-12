#include "SFML/Graphics.hpp"

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

public:
    Clock(float t);
    void update();
    void update(float n);
    void restart();
    void set_threshold(float t);
    float get_tick();
    float get_time();
    float get_total_time();
    float get_threshold();
    float get_initial_time();
    bool need_restart();
};

#endif