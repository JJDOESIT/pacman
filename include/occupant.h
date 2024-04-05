#include "enum.h"
#include <iostream>

#ifndef _OCCUPANT_
#define _OCCUPANT_

class Occupant
{
private:
    int x_position;
    int y_position;
    int type;
    int direction;

public:
    void set_position(int x, int y);
    int get_x_position();
    int get_y_position();
    void set_direction(int d);
    int get_direction();

    void set_type(int t);
    int get_type();
    void print_type();
};

#endif