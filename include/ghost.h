#include "occupant.h"

#ifndef _GHOST_
#define _GHOST_

class Ghost : public Occupant
{
private:
    int mode = 0;
    int target_tile[2] = {-1, -1};

public:
    Ghost(int x, int y, int d);
    void set_mode(int m);
    int get_mode();
    int get_target_x_tile();
    int get_target_y_tile();
    void set_target_tile(int x, int y);
};

#endif