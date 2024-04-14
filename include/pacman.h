#include "occupant.h"

#ifndef _PACMAN_
#define _PACMAN_

class Pacman : public Occupant
{

private:
    int initial_position[2] = {-1, -1};
    int initial_direction;
    int animation_state = 1;

public:
    Pacman(int x, int y, int d);
    int get_initial_x();
    int get_initial_y();
    int get_initial_direction();
    void set_animation_state(int state);
    int get_animation_state();
};

#endif