#include "state_manager.h"

// Push a timing and ghost mode into the list
void State_Manager::push(int timing, int mode)
{
    ghost_timings.push_back(std::vector<int>{timing, mode});
    if (ghost_timings.size() == 1)
    {
        ghost_mode_clock.set_threshold(ghost_timings[0][0]);
    }
}

// Update the ghost mode state
void State_Manager::update_state()
{
    ghost_mode_clock.update();
    if (ghost_mode_clock.need_restart())
    {
        index = ++index % ghost_timings.size();
        ghost_mode_clock.set_threshold(ghost_timings[index][0]);
        ghost_mode_clock.restart();
    }
}

// Return the current ghost mode (chase or scatter)
int State_Manager::get_ghost_mode()
{
    return ghost_timings[index][1];
}
