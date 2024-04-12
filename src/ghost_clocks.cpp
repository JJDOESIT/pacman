#include "ghost_clocks.h"

// Initilize the ghost clocks
Ghost_Clocks::Ghost_Clocks(float inital_time)
{
    clocks[ghosts_types::BLINKY] = new Clock{inital_time};
    clocks[ghosts_types::PINKY] = new Clock{inital_time};
    clocks[ghosts_types::INKY] = new Clock{inital_time};
    clocks[ghosts_types::CLYDE] = new Clock{inital_time};
}

// Update the ghost clocks
void Ghost_Clocks::update_all()
{
    for (int i = 0; i < 4; i++)
    {
        clocks[i]->update();
    }
}

// Restart the ghost clocks
void Ghost_Clocks::restart_all()
{
    for (int i = 0; i < 4; i++)
    {
        clocks[i]->restart();
    }
}
