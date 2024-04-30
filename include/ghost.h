#ifndef _GHOST_
#define _GHOST_

#include "occupant.h"

class Ghost : public Occupant
{
private:
    int type;
    int mode = 0;
    int initial_position[2] = {-1, -1};
    int initial_direction;
    int target_tile[2] = {-1, -1};
    int best_move[2] = {-1, -1};

public:
    Ghost(int x, int y, int d, int t);
    void set_mode(int m);
    int get_type();
    int get_mode();
    int get_initial_x();
    int get_initial_y();
    int get_initial_direction();
    int get_target_x_tile();
    int get_target_y_tile();
    int get_best_x_tile();
    int get_best_y_tile();
    void set_target_tile(int x, int y);
    void set_best_move(int x, int y);
};

#endif