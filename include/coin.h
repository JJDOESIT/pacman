#ifndef _COIN_
#define _COIN_

#include "occupant.h"

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