#include "occupant.h"

#ifndef _PACMAN_
#define _PACMAN_

class Pacman : public Occupant
{

private:
    int animation_state = 1;

public:
    Pacman(int x, int y, int d);
    void set_animation_state(int state);
    int get_animation_state();
};

#endif