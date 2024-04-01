#include "occupant.h"

#ifndef _PORTAL_
#define _PORTAL_

class Portal : public Occupant
{
private:
    Portal *link;
    int id;

public:
    Portal(int x, int y, int direction, int unique_id);
    int get_id();
    void set_link(Portal *other_portal);
    Portal *get_link();
};

#endif