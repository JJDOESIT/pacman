#include "text_manager.h"

// Set the text to correspond to the given parameters (text, size, color)
void Text_Manager::set_text(sf::Text *t, std::string text, int size, sf::Color color)
{
    t->setString(text);
    t->setCharacterSize(size);
    t->setFillColor(color);
}

// Set the font of the given text
void Text_Manager::set_font(sf::Text *t, sf::Font *f, std::string font_name)
{
    if (!f->loadFromFile(font_name))
    {
        std::cout << "Error: Cannot open font file ..." << std::endl;
        exit(1);
    };
    t->setFont(*f);
}

// Set the position of the given text
void Text_Manager::set_position(sf::Text *t, float x, float y)
{
    t->setPosition(sf::Vector2f(x, y));
}
