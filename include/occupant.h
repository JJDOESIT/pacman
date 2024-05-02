#ifndef _OCCUPANT_
#define _OCCUPANT_

#include "enum.h"
#include "SFML/Graphics.hpp"

class Occupant
{
private:
    int x_position;
    int y_position;
    int type;
    int direction;
    sf::RectangleShape cell;

public:
    void set_position(int x, int y);
    int get_x_position();
    int get_y_position();
    void set_direction(int d);
    int get_direction();

    sf::RectangleShape *get_cell();
    void set_type(int t);
    int get_type();
};

#endif