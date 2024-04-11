#include "occupant.h"

#ifndef _POWER_
#define _POWER_

class Power : public Occupant
{
private:
    bool toggled;
    int type;

public:
    Power(int x, int y, int type, bool toggle = true);
    void set_toggled(bool t);
    void set_type(int type);
    int get_type();
    bool get_toggled();
};

#endif