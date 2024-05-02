#ifndef _BUTTONS_
#define _BUTTONS_

#include "button.h"

#include <vector>

class Buttons
{
private:
    std::vector<Button *> buttons;

public:
    ~Buttons();
    std::vector<Button *> *get_buttons();
    void push(Button *button);
    void clear();
};

#endif