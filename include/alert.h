#ifndef _ALERT_
#define _ALERT_

#include "SFML/Graphics.hpp"
#include "text_manager.h"
#include "button.h"
#include "config.h"

class Alert
{
private:
    bool toggled = false;
    sf::RectangleShape cell;
    sf::Text text;
    sf::Font font;
    Button *dismiss = nullptr;
    void set_size(int width, int height);
    void set_position(int x, int y);

public:
    void initilize(int x, int y, int width, int height, int char_size, sf::Color rect_color, sf::Color text_color, std::string t = "");
    ~Alert();
    bool is_toggled();
    void set_toggled(bool t);
    sf::RectangleShape *get_cell();
    sf::Text *get_text();
    void set_text(std::string t);
    Button *get_dismiss_button();
    void reset();
};

#endif