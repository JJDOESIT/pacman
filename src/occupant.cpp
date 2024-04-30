#include "occupant.h"

// Set the position of the occupant
void Occupant::set_position(int x, int y)
{
    x_position = x;
    y_position = y;
}

// Return the x position of the occupant within the board
int Occupant::get_x_position()
{
    return x_position;
}

// Return the y position of the occupant within the board
int Occupant::get_y_position()
{
    return y_position;
}

// Set the direction of the occupant
void Occupant::set_direction(int d)
{
    direction = d;
}

// Return the direction of the occupant
int Occupant::get_direction()
{
    return direction;
}

// Set the type of the occupant
void Occupant::set_type(int t)
{
    type = t;
}

// Return the type of the occupant (ex: WALL, COIN, GHOST, etc)
int Occupant::get_type()
{
    return type;
}