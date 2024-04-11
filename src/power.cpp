#include "power.h"

Power::Power(int x, int y, int type, bool toggle)
{
    Occupant::set_type(type::POWER);
    Occupant::set_position(x, y);
    Power::type = type;
    toggled = toggle;
}

// Set the power up to be toggled or not toggled
void Power::set_toggled(bool t)
{
    toggled = t;
}

// Set the type of power up
void Power::set_type(int type)
{
    Power::type = type;
}

// Get the type of power up
int Power::get_type()
{
    return Power::type;
}

// Return whether the power up is toggled or not
bool Power::get_toggled()
{
    return toggled;
}