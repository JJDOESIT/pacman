#include "pacman.h"

Pacman::Pacman(int x, int y, int d)
{
    Occupant::set_type(type::PLAYER);
    Occupant::set_position(x, y);
    Occupant::set_direction(d);
    initial_position[0] = x;
    initial_position[1] = y;
}

// Return the initial x position of pacman
int Pacman::get_initial_x()
{
    return initial_position[0];
}

// Return the initial y position of pacman
int Pacman::get_initial_y()
{
    return initial_position[1];
}

// Set pacman's animation state
void Pacman::set_animation_state(int state)
{
    animation_state = state;
}

// Return pacman's animation state
int Pacman::get_animation_state()
{
    return animation_state;
}
