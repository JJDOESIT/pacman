#include "text_manager.h"

Text_Manager::Text_Manager(std::string font_name)
{
    if (!f.loadFromFile(font_name))
    {
        exit(1);
    };
    t.setFont(f);
}

// Set the text to correspond to the given parameters (text, size, color)
void Text_Manager::set_text(std::string text, int size, sf::Color color)
{
    t.setString(text);
    t.setCharacterSize(size);
    t.setFillColor(color);
}

// Return a copy of the text
sf::Text Text_Manager::get_text()
{
    return t;
}
