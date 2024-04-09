#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#ifndef _TEXT_MANAGER_
#define _TEXT_MANAGER_

class Text_Manager
{
private:
    sf::Font f;
    sf::Text t;

public:
    Text_Manager(std::string font_name);
    void set_text(std::string text, int size, sf::Color color);
    sf::Text get_text();
};

#endif