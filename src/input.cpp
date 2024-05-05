#include "input.h"

Input::Input(int x, int y, int width, int height, int char_size, sf::Color rect_color, sf::Color input_text_color, sf::Color label_text_color, std::string label)
{
    Input::input_cell.setSize(sf::Vector2f(width, height));
    Input::input_cell.setPosition(sf::Vector2f(x, y));
    Input::input_cell.setFillColor(rect_color);
    Text_Manager::set_font(&text, &font, Config::FONT_DIR + "lyons.ttf");
    Text_Manager::set_font(&label_text, &font, Config::FONT_DIR + "lyons.ttf");
    Text_Manager::set_text(&text, "TEST", char_size, input_text_color);
    Text_Manager::set_text(&label_text, label, char_size, label_text_color);
    Text_Manager::set_position(&text, input_cell.getPosition().x + 5, (input_cell.getPosition().y + (input_cell.getSize().y / 2)) - (text.getGlobalBounds().height / 2));
    Text_Manager::set_position(&label_text, input_cell.getPosition().x - label_text.getGlobalBounds().width - 5, (input_cell.getPosition().y + (input_cell.getSize().y / 2)) - (label_text.getGlobalBounds().height / 2));
    text.setString("");
}

// Return the input_cell associated with the button
sf::RectangleShape *Input::get_cell()
{
    return &input_cell;
}

// Set a call-back function
void Input::set_function(std::function<void()> f)
{
    Input::f = f;
}

// Run the call-back function
void Input::run_function()
{
    f();
}

// Return a pointer to the text instance
sf::Text *Input::get_text()
{
    return &text;
}

// Return a pointer to the label text instance
sf::Text *Input::get_label_text()
{
    return &label_text;
}

// Return a pointer to the font instance
sf::Font *Input::get_font()
{
    return &font;
}

// Update the text
void Input::update_text(std::string c)
{
    text.setString(text.getString() + c);
}

// Update the text
void Input::update_text(sf::String c)
{
    text.setString(text.getString() + c.toAnsiString());
}

// Delete a character
void Input::delete_character()
{
    std::string new_text;
    for (int c = 0; c < text.getString().getSize() - 1; c++)
    {
        new_text += text.getString()[c];
    }
    text.setString(new_text);
}

// Return the length of the input text
int Input::get_length_of_text()
{
    return text.getString().getSize();
}
