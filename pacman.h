#include "occupant.h"

#ifndef _PACMAN_
#define _PACMAN_

class Pacman : public Occupant
{
private:
    int direction = 1;

public:
    Pacman(int x, int y);
    void set_direction(int d);
    int get_direction();
};

#endif