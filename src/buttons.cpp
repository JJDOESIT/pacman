#include "buttons.h"

// Deconstruct the button list
Buttons::~Buttons()
{
    clear();
}

// Return a pointer to the button list
std::vector<Button *> *Buttons::get_buttons()
{
    return &buttons;
}

// Add a button to the button list
void Buttons::push(Button *button)
{
    buttons.push_back(button);
}

// Clear the button list
void Buttons::clear()
{
    for (int b = buttons.size() - 1; b >= 0; b--)
    {
        delete buttons[b];
        buttons.pop_back();
    }
}
