#include "speed_manager.h"

// Initilize the ghost clocks
Speed_Manager::Speed_Manager(State_Manager *state_manager, float inital_time)
{
    Speed_Manager::state_manager = state_manager;
    Speed_Manager::initial_time = inital_time;
    ghost_clocks[ghosts_types::BLINKY] = new Clock{inital_time};
    ghost_clocks[ghosts_types::PINKY] = new Clock{inital_time};
    ghost_clocks[ghosts_types::INKY] = new Clock{inital_time};
    ghost_clocks[ghosts_types::CLYDE] = new Clock{inital_time};
}

// Update the ghost clocks
void Speed_Manager::update_all()
{
    for (int i = 0; i < 4; i++)
    {
        ghost_clocks[i]->update();
    }
}

// Restart all clocks
void Speed_Manager::restart_all()
{
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

// Return the initial time of the ghost clocks
float Speed_Manager::get_initial_time()
{
    return initial_time;
}

void Speed_Manager::update_ghost_speed(int ghost, float time)
{
    if (state_manager->get_ghost_state(ghost) != ghost_states::HEADING_BACK)
    {
        ghost_clocks[ghost]->set_threshold(time);
    }
}
