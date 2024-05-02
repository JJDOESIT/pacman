#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#ifndef _TEXT_MANAGER_
#define _TEXT_MANAGER_

class Text_Manager
{

public:
    static void set_text(sf::Text *t, std::string text, int size, sf::Color color);
    static void set_font(sf::Text *t, sf::Font *f, std::string font_name);
    static void set_position(sf::Text *t, float x, float y);
};

#endif