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
    int n_coins;
    int n_initial_coins;

public:
    void update(int n);
    void reset();
    void stringify();
    void increament_coins();
    void decreament_coins();
    void set_n_initial_coins(int n);
    bool has_won();
    int get_n_points();
    int get_n_coins();
    sf::Text *get_text();
    sf::Font *get_font();
};

#endif