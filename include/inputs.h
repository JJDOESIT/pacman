#ifndef _INPUTS_
#define _INPUTS_

#include "input.h"

#include <vector>

class Inputs
{
private:
    std::vector<Input *> inputs;
    int selected;

public:
    ~Inputs();
    std::vector<Input *> *get_inputs();
    void push(Input *input);
    void clear();
    void set_selected(int index);
    int get_selected();
    void reset();
};

#endif