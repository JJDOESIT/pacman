#ifndef _INPUT_
#define _INPUT_

#include "SFML/Graphics.hpp"
#include "text_manager.h"
#include "config.h"

#include <functional>
#include <string>

class Input
{
private:
    sf::RectangleShape input_cell;
    std::function<void()> f;
    sf::Text text;
    sf::Text label_text;
    sf::Font font;

public:
    Input(int x, int y, int width, int height, int char_size, sf::Color rect_color, sf::Color input_text_color, sf::Color label_text_color, std::string label);
    sf::RectangleShape *get_cell();
    void set_function(std::function<void()> f);
    void run_function();
    sf::Text *get_text();
    sf::Text *get_label_text();
    sf::Font *get_font();
    void update_text(std::string c);
    void update_text(sf::String c);
    void delete_character();
    int get_length_of_text();
};

#endif