#include "button.h"

Button::Button(int x, int y, int width, int height, int char_size, sf::Color rect_color, sf::Color text_color, std::string t)
{
    Button::text.setString(t);
    Button::cell.setSize(sf::Vector2f(width, height));
    Button::cell.setPosition(sf::Vector2f(x, y));
    Button::cell.setFillColor(rect_color);
    Text_Manager::set_font(&text, &font, "fonts/ranchos.otf");
    Text_Manager::set_text(&text, text.getString(), char_size, text_color);
    Text_Manager::set_position(&text, cell.getPosition().x + (cell.getSize().x / 2) - (text.getGlobalBounds().width / 2), cell.getPosition().y + (cell.getSize().y / 2) - (text.getGlobalBounds().height / 2));
}

// Return the cell associated with the button
sf::RectangleShape *Button::get_cell()
{
    return &cell;
}

// Set a call-back function
void Button::set_function(std::function<void()> f)
{
    Button::f = f;
}

// Run the call-back function
void Button::run_function()
{
    f();
}

// Return a pointer to the text instance
sf::Text *Button::get_text()
{
    return &text;
}

// Return a pointer to the font instance
sf::Font *Button::get_font()
{
    return &font;
}
