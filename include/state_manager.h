#include "clock.h"
#include "enum.h"
#include <iostream>

#include <vector>

#ifndef _STATE_MANAGER_
#define _STATE_MANAGER_

class State_Manager
{
private:
    Clock ghost_mode_clock{0};
    int index = 0;
    std::vector<std::vector<int>> ghost_timings;

public:
    void push(int timing, int mode);
    void update_state();
    int get_ghost_mode();
};

#endif