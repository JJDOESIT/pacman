#ifndef _STATE_MANAGER_
#define _STATE_MANAGER_

#include "clock.h"
#include "enum.h"
#include "occupant.h"
#include "ghost.h"
#include "config.h"

#include <functional>
#include <vector>
#include <string>

class State_Manager
{
private:
    int initial_state;

    int mode_index = 0;
    int overide_ghost_mode = -1;
    Clock ghost_mode_clock{0};
    std::vector<std::vector<int>> ghost_timings;

    Clock ghost_state_clocks[4] = {Clock{0}, Clock{0}, Clock{0}, Clock{0}};
    int ghost_states[4] = {ghost_states::ESCAPING, ghost_states::ESCAPING, ghost_states::ESCAPING, ghost_states::ESCAPING};

    int ghost_escape_tiles[4][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};

public:
    State_Manager(int initial_state);
    void push(int timing, int mode);
    void update_mode(int overide_mode = -1);
    void overide_mode(int timing, int mode);
    int get_ghost_mode();
    Clock *get_ghost_mode_clock();

    void update_states();
    void set_ghost_state(int ghost, int state);
    int get_ghost_state(int ghost);
    void set_all_ghost_states(int state);
    Clock *get_ghost_state_clock(int ghost);

    void set_ghost_escape_tile(int ghost, int x, int y);
    int get_ghost_escape_x(int ghost);
    int get_ghost_escape_y(int ghost);
    bool has_escaped(Occupant *ghost);

    void reset();
};

#endif