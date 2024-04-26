#include "tile.h"

Tile::Tile(int type, int specific_type, int toggled)
{
    Tile::type = type;
    Tile::specific_type = specific_type;
    Tile::toggled = toggled;
}

// Return the type of the tile
int Tile::get_type()
{
    return type;
}

// Return the specific type of the tile
int Tile::get_specific_type()
{
    return specific_type;
}

// Return whether the tile is toggled or not
int Tile::get_toggled()
{
    return toggled;
}

// Toggle is_selected
void Tile::set_is_selected(bool selected)
{
    is_selected = selected;
}

// Return whether the tile was clicked by the user or not
bool Tile::get_is_selected()
{
    return is_selected;
}

// Return a pointer to the rect of the tile
sf::RectangleShape &Tile::get_rect()
{
    return rect;
}
