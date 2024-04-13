#include "clock.h"
#include "enum.h"
#include "occupant.h"
#include "ghost.h"
#include <iostream>

#include <vector>
#include <string>

#ifndef _STATE_MANAGER_
#define _STATE_MANAGER_

class State_Manager
{
private:
    Clock ghost_mode_clock{0};
    int mode_index = 0;
    std::vector<std::vector<int>> ghost_timings;
    int overide_ghost_mode = -1;

    Clock ghost_state_clocks[4] = {Clock{0}, Clock{0}, Clock{0}, Clock{0}};
    int ghost_states[4] = {ghost_states::ESCAPING, ghost_states::ESCAPING, ghost_states::ESCAPING, ghost_states::ESCAPING};
    int ghost_state_overides[4] = {-1, -1, -1, -1};

    int ghost_escape_tiles[4][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};

public:
    void push(int timing, int mode);
    void update_mode(int overide_mode = -1);
    void overide_mode(int timing, int mode);
    int get_ghost_mode();
    Clock *get_ghost_mode_clock();

    void update_states();
    void set_ghost_state(int ghost, int state);
    int get_ghost_state(int ghost);
    void overide_state(int timing, int state, int ghost);
    void set_all_ghost_states(int state);

    void set_ghost_escape_tile(int ghost, int x, int y);
    int get_ghost_escape_x(int ghost);
    int get_ghost_escape_y(int ghost);
    bool has_escaped(Occupant *ghost);
};

#endif