#include "inputs.h"

// Deconstruct the input list
Inputs::~Inputs()
{
    clear();
}

// Return a pointer to the input list
std::vector<Input *> *Inputs::get_inputs()
{
    return &inputs;
}

// Add a input to the input list
void Inputs::push(Input *input)
{
    inputs.push_back(input);
}

// Clear the input list
void Inputs::clear()
{
    for (int i = inputs.size() - 1; i >= 0; i--)
    {
        delete inputs[i];
        inputs.pop_back();
    }
}

// Set the selected input
void Inputs::set_selected(int index)
{
    selected = index;
}

// Return the selected input
int Inputs::get_selected()
{
    return selected;
}

// Reset all input texts
void Inputs::reset()
{
    for (int i = 0; i < inputs.size(); i++)
    {
        inputs[i]->get_text()->setString("");
    }
}
