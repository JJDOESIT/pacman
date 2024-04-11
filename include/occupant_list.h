#include "occupant.h"
#include "state_manager.h"

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
    void pop_specific_occupant(Occupant *occupant);
    void set_state_of_all_ghosts(State_Manager *state_manager, int state);
    std::vector<Occupant *> &get_oc_list();
    void print_occupant_list();
    Occupant *find_occupant(int type);
};

#endif