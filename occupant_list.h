#include "occupant.h"

#include <vector>

#ifndef _OCCUPANT_LIST_
#define _OCCUPANT_LIST_

class Occupant_List
{
private:
    std::vector<Occupant *> oc_list;

public:
    Occupant_List(Occupant *occupant);
    void push(Occupant *occupant);
    void pop_occupant(int type);
    std::vector<Occupant *> &get_oc_list();
    void print_occupant_list();
    Occupant *find_occupant(int type);
};

#endif