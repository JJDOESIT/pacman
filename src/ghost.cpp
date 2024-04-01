#include "ghost.h"

Ghost::Ghost(int x, int y, int d)
{
    Occupant::set_type(type::GHOST);
    Occupant::set_position(x, y);
    Occupant::set_direction(d);
}

// Set the ghost's mode
void Ghost::set_mode(int m)
{
    mode = m;
}

// Return the ghost's mode
int Ghost::get_mode()
{
    return mode;
}

// Return the x position of the target tile
int Ghost::get_target_x_tile()
{
    return target_tile[0];
}

// Return the y position of the target tile
int Ghost::get_target_y_tile()
{
    return target_tile[1];
}

// Set the ghost's target tile
void Ghost::set_target_tile(int x, int y)
{
    target_tile[0] = x;
    target_tile[1] = y;
}
