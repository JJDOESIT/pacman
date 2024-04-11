#include "coin.h"

Coin::Coin(int x, int y, bool toggle)
{
    Occupant::set_type(type::COIN);
    Occupant::set_position(x, y);
    toggled = toggle;
}

// Set the coin to be toggled or not toggled
void Coin::set_toggled(bool t)
{
    toggled = t;
}

// Return whether the coin is toggled or not
bool Coin::get_toggled()
{
    return toggled;
}
