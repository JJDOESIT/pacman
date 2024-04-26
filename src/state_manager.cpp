#include "state_manager.h"

State_Manager::State_Manager(int initial_state)
{
    State_Manager::initial_state = initial_state;
}

// Push a timing and ghost mode into the list
void State_Manager::push(int timing, int mode)
{
    ghost_timings.push_back(std::vector<int>{timing, mode});
    if (ghost_timings.size() == 1)
    {
        ghost_mode_clock.set_threshold(ghost_timings[0][0]);
    }
}

// TODO: Fix the problem where the cycles will go out of sync if overide is set
// Update the ghost mode state
void State_Manager::update_mode(int overide_mode)
{
    ghost_mode_clock.update();
    if (ghost_mode_clock.need_restart())
    {
        if (overide_ghost_mode != -1)
        {
            overide_ghost_mode = -1;
        }
        else
        {
            mode_index = ++mode_index % ghost_timings.size();
            ghost_mode_clock.set_threshold(ghost_timings[mode_index][0]);
        }
        ghost_mode_clock.restart();
    }
}

// Overide the current mode for a set amount of time in milliseconds
void State_Manager::overide_mode(int timing, int mode)
{
    overide_ghost_mode = mode;
    ghost_mode_clock.set_threshold(timing);
    ghost_mode_clock.restart();
}

// Return the current ghost mode (chase or scatter)
int State_Manager::get_ghost_mode()
{
    return overide_ghost_mode == -1 ? ghost_timings[mode_index][1] : overide_ghost_mode;
}

Clock *State_Manager::get_ghost_mode_clock()
{
    return &ghost_mode_clock;
}

// Update the states if needed
void State_Manager::update_states()
{
    for (int i = 0; i < 4; i++)
    {
        ghost_state_clocks[i].update();
        if (ghost_state_clocks[i].need_restart())
        {
            ghost_state_clocks[i].restart();
        }
    }
}

// Set the state of the given ghost
void State_Manager::set_ghost_state(int ghost, int state)
{
    ghost_states[ghost] = state;
}

// Return the state of the given ghost (escaping, free, or disabled, or heading back)
int State_Manager::get_ghost_state(int ghost)
{
    return ghost_states[ghost];
}

// Set the state of all ghosts
void State_Manager::set_all_ghost_states(int state)
{
    set_ghost_state(ghosts_types::BLINKY, state);
    set_ghost_state(ghosts_types::PINKY, state);
    set_ghost_state(ghosts_types::INKY, state);
    set_ghost_state(ghosts_types::CLYDE, state);
}

// Return the state of the given ghost
Clock *State_Manager::get_ghost_state_clock(int ghost)
{
    return &ghost_state_clocks[ghost];
}

// Set the escape tile of the given ghost
void State_Manager::set_ghost_escape_tile(int ghost, int x, int y)
{
    ghost_escape_tiles[ghost][0] = x;
    ghost_escape_tiles[ghost][1] = y;
}

// Return the escape x tile of the given ghost
int State_Manager::get_ghost_escape_x(int ghost)
{
    return ghost_escape_tiles[ghost][0];
}

// Return the escape y tile of the given ghost
int State_Manager::get_ghost_escape_y(int ghost)
{
    return ghost_escape_tiles[ghost][1];
}

// Return whether the ghost has escape from the den or not
bool State_Manager::has_escaped(Occupant *ghost)
{
    return ghost_escape_tiles[static_cast<Ghost *>(ghost)->get_type()][0] == ghost->get_x_position() && ghost_escape_tiles[static_cast<Ghost *>(ghost)->get_type()][1] == ghost->get_y_position();
}

// Reset the states of all ghosts
void State_Manager::reset()
{
    for (int ghost = 0; ghost < 4; ghost++)
    {
        ghost_state_clocks[ghost].reset();
        ghost_states[ghost] = initial_state;
    }
    ghost_mode_clock.reset();
    mode_index = 0;
    overide_ghost_mode = -1;
}
