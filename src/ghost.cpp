#include "ghost.h"

Ghost::Ghost(int x, int y, int d)
{
    Occupant::set_type(type::GHOST);
    Occupant::set_position(x, y);
    Occupant::set_direction(d);
    initial_position[0] = x;
    initial_position[1] = y;
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

// Return the initial x position of the ghost
int Ghost::get_initial_x()
{
    return initial_position[0];
}

// Return the initial y position of the ghost
int Ghost::get_initial_y()
{
    return initial_position[1];
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

// Return the x position of the best move
int Ghost::get_best_x_tile()
{
    return best_move[0];
}

// Return the y position of the best move
int Ghost::get_best_y_tile()
{
    return best_move[1];
}

// Set the ghost's target tile
void Ghost::set_target_tile(int x, int y)
{
    target_tile[0] = x;
    target_tile[1] = y;
}

// Set the ghost's best move
void Ghost::set_best_move(int x, int y)
{
    best_move[0] = x;
    best_move[1] = y;
}
