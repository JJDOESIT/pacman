#include "pacman.h"

Pacman::Pacman(int x, int y, int d)
{
    Occupant::set_type(type::PLAYER);
    Occupant::set_position(x, y);
    Occupant::set_direction(d);
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
