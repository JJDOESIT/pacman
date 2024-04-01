#include "wall.h"

Wall::Wall(int x, int y, int wall_t)
{
    Occupant::set_type(type::WALL);
    Occupant::set_position(x, y);
    wall_type = wall_t;
}
int Wall::get_wall_type()
{
    return wall_type;
}
