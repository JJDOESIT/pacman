#include "portal.h"

Portal::Portal(int x, int y, int direction, int unique_id)
{
    Occupant::set_position(x, y);
    Occupant::set_type(type::PORTAL);
    Occupant::set_direction(direction);
    id = unique_id;
}

// Return the portal's unique id
int Portal::get_id()
{
    return id;
}

// Connect the two portal's together
void Portal::set_link(Portal *other_portal)
{
    link = other_portal;
}

// Return the connected portal
Portal *Portal::get_link()
{
    return link;
}
