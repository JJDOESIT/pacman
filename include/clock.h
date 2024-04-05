#include "SFML/Graphics.hpp"

#ifndef _CLOCK_
#define _CLOCK_

class Clock
{
private:
    float tick;
    float threshold;
    float time;
    sf::Clock c;
    sf::Time dt;

public:
    Clock(float t);
    void update();
    void update(float n);
    void restart();
    float get_tick();
    float get_time();
    float get_threshold();
    bool need_restart();
};

#endif