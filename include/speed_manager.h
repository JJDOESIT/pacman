#include "clock.h"
#include "enum.h"
#include "state_manager.h"
#include <functional>

#ifndef _GHOST_CLOCKS_
#define _GHOST_CLOCKS_

class Speed_Manager
{
private:
    State_Manager *state_manager;

public:
    Clock *ghost_clocks[4];
    Clock *pacman_clock;
    Speed_Manager(State_Manager *state_manager, float pacman_initial_time, float ghost_inital_time);
    void update_all();
    void restart_all();
    void reset_all();
    void set_threshold(int ghost, float time);
    void set_threshold_all(float time);
    float get_initial_time(int type);
    void update_ghost_speed(int ghost, float time);
};

#endif