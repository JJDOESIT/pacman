

#ifndef _TILE_
#define _TILE_

#include "SFML/Graphics.hpp"

class Tile
{
private:
    int type;
    int specific_type;
    int toggled;
    sf::RectangleShape rect;
    bool is_selected;

public:
    Tile(int type, int specific_type = 0, int toggled = true);
    int get_type();
    int get_specific_type();
    int get_toggled();
    sf::RectangleShape &get_rect();
};

#endif