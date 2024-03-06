#include "occupant.h"

#ifndef _COIN_
#define _COIN_

class Coin : public Occupant
{

private:
    bool toggled;

public:
    Coin(int x, int y, bool toggle = true);
    void set_toggled(bool t);
    bool get_toggled();
};

#endif