#include "pacman.h"

Pacman::Pacman(int x, int y)
{
    Occupant::set_type(type::PLAYER);
    Occupant::set_position(x, y);
}

// Set pacman's current direction (up, right, down, left)
void Pacman::set_direction(int d)
{
    direction = d;
}

// Return pacman's current direction (up, right, down, left)
int Pacman::get_direction()
{
    return direction;
}