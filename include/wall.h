#ifndef _WALL_
#define _WALL_

#include "occupant.h"

class Wall : public Occupant
{
private:
    int wall_type;

public:
    Wall(int x, int y, int wall_t);
    int get_wall_type();
};

#endif