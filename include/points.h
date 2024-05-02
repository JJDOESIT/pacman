#ifndef _POINTS_
#define _POINTS_

#include "SFML/Graphics.hpp"
#include <iostream>

class Points
{
private:
    const int POINT_STRING_SIZE = 7;
    int n_points = 0;
    char points_array[8] = {'0', '0', '0', '0', '0', '0', '0', '\0'};
    sf::Text text;
    sf::Font font;

public:
    void update(int n);
    void reset();
    void stringify();
    sf::Text *get_text();
    sf::Font *get_font();
};

#endif