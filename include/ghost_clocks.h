#include "clock.h"
#include "enum.h"

#ifndef _GHOST_CLOCKS_
#define _GHOST_CLOCKS_

class Ghost_Clocks
{
public:
    Clock *clocks[4];

    Ghost_Clocks(float inital_time);
    void update_all();
    void restart_all();
    void set_threshold_all(float time);
};

#endif