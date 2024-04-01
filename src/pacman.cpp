#include "pacman.h"

Pacman::Pacman(int x, int y, int d)
{
    Occupant::set_type(type::PLAYER);
    Occupant::set_position(x, y);
    Occupant::set_direction(d);
}
