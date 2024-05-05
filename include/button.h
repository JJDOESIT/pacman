#ifndef _BUTTON_
#define _BUTTON_

#include "SFML/Graphics.hpp"
#include "text_manager.h"
#include "config.h"

#include <functional>
#include <string>

class Button
{
private:
    sf::RectangleShape cell;
    std::function<void()> f;
    sf::Text text;
    sf::Font font;

public:
    Button(int x, int y, int width, int height, int char_size, sf::Color rect_color, sf::Color text_color, std::string t);
    sf::RectangleShape *get_cell();
    void set_function(std::function<void()> f);
    void run_function();
    sf::Text *get_text();
    sf::Font *get_font();
};

#endif