#include "speed_manager.h"

// Initilize the ghost clocks
Speed_Manager::Speed_Manager(State_Manager *state_manager, float pacman_initial_time, float ghost_initial_time)
{
    Speed_Manager::state_manager = state_manager;
    pacman_clock = new Clock{pacman_initial_time};
    ghost_clocks[ghosts_types::BLINKY] = new Clock{ghost_initial_time};
    ghost_clocks[ghosts_types::PINKY] = new Clock{ghost_initial_time};
    ghost_clocks[ghosts_types::INKY] = new Clock{ghost_initial_time};
    ghost_clocks[ghosts_types::CLYDE] = new Clock{ghost_initial_time};
}

// Update all the speed clocks
void Speed_Manager::update_all()
{
    pacman_clock->update();
    for (int i = 0; i < 4; i++)
    {
        ghost_clocks[i]->update();
    }
}

// Restart all the speed clocks
void Speed_Manager::restart_all()
{
    pacman_clock->restart();
    for (int i = 0; i < 4; i++)
    {
        ghost_clocks[i]->restart();
    }
}

// Reset all clocks
void Speed_Manager::reset_all()
{
    for (int i = 0; i < 4; i++)
    {
        ghost_clocks[i]->reset();
    }
}

// Set the threshold speed of a given ghost
void Speed_Manager::set_threshold(int ghost, float time)
{
    ghost_clocks[ghost]->set_threshold(time);
}

// Set the threshold of all clocks
void Speed_Manager::set_threshold_all(float time)
{
    for (int i = 0; i < 4; i++)
    {
        ghost_clocks[i]->set_threshold(time);
    }
}

// Return the initial time of the given character type (pacman or ghost)
float Speed_Manager::get_initial_time(int type)
{
    if (type == type::PLAYER)
    {
        return pacman_clock->get_initial_time();
    }
    else if (type == type::GHOST)
    {
        return ghost_clocks[0]->get_initial_time();
    }
    return -1;
}

void Speed_Manager::update_ghost_speed(int ghost, float time)
{
    if (state_manager->get_ghost_state(ghost) != ghost_states::HEADING_BACK)
    {
        ghost_clocks[ghost]->set_threshold(time);
    }
}
