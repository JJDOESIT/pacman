#include "alert.h"

Alert::~Alert()
{
    delete dismiss;
}

// Set the size of the cell
void Alert::set_size(int width, int height)
{
    cell.setSize(sf::Vector2f(width, height));
}

// Set the position of the cell
void Alert::set_position(int x, int y)
{
    cell.setPosition(sf::Vector2f(x, y));
}

// Return a pointer to the alert cell
sf::RectangleShape *Alert::get_cell()
{
    return &cell;
}

// Set the alert toggle
void Alert::set_toggled(bool t)
{
    toggled = t;
}

// Initilize an alert
void Alert::initilize(int x, int y, int width, int height, int char_size, sf::Color rect_color, sf::Color text_color, std::string t)
{
    toggled = false;
    set_size(width, height);
    set_position(x, y);
    Alert::cell.setFillColor(rect_color);
    Text_Manager::set_font(&text, &font, Config::FONT_DIR + "lyons.ttf");
    Text_Manager::set_text(&text, t, char_size, text_color);
    Text_Manager::set_position(&text, cell.getPosition().x + (cell.getSize().x / 2) - (text.getGlobalBounds().width / 2), cell.getPosition().y + (cell.getSize().y / 2) - (text.getGlobalBounds().height / 2));
    if (dismiss)
    {
        delete dismiss;
    }
    dismiss = new Button(x + width, y, width / 5, height, char_size, sf::Color(234, 234, 234), sf::Color::Black, "X");
}

// Return a pointer to the dismiss button
Button *Alert::get_dismiss_button()
{
    return dismiss;
}

// Return a pointer to the alert text
sf::Text *Alert::get_text()
{
    return &text;
}

// Set the message of the alert
void Alert::set_text(std::string t)
{
    text.setString(t);
    Text_Manager::set_position(&text, cell.getPosition().x + (cell.getSize().x / 2) - (text.getGlobalBounds().width / 2), cell.getPosition().y + (cell.getSize().y / 2) - (text.getGlobalBounds().height / 2));
}

// Reset the state of the alert
void Alert::reset()
{
    text.setString("");
    toggled = false;
}

// Return whether the alert is toggled or not
bool Alert::is_toggled()
{
    return toggled;
}
