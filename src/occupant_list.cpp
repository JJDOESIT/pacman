#include "occupant_list.h"

Occupant_List::Occupant_List(Occupant *occupant)
{
    oc_list.push_back(occupant);
}

// Push the given occupant onto the end of the list
void Occupant_List::push(Occupant *occupant)
{
    oc_list.push_back(occupant);
}

// Remove the first occurence of the given occupant
void Occupant_List::pop_occupant(int type)
{
    int count = 0;
    while (count < oc_list.size())
    {
        if (oc_list[count]->get_type() == type)
        {
            oc_list.erase(oc_list.begin() + count);
            break;
        }
        count++;
    }
}

// Given a pointer to an occupant, pop that occupant from the list
void Occupant_List::pop_specific_occupant(Occupant *occupant)
{
    int count = 0;
    while (count < oc_list.size())
    {
        if (oc_list[count] == occupant)
        {
            oc_list.erase(oc_list.begin() + count);
            break;
        }
        count++;
    }
}

void Occupant_List::set_state_of_all_ghosts(State_Manager *state_manager, int state)
{
    int count = 0;
    while (count < oc_list.size())
    {
        if (oc_list[count]->get_type() == type::GHOST)
        {
            state_manager->set_ghost_state(static_cast<Ghost *>(oc_list[count])->get_type(), state);
        }
        count++;
    }
}

// Return the first occurence of the given occupant
Occupant *Occupant_List::find_occupant(int type)
{
    int count = 0;
    while (count < oc_list.size())
    {
        if (oc_list[count]->get_type() == type)
        {
            return oc_list[count];
        }
        count++;
    }
    return nullptr;
}

// Print the occupant list
void Occupant_List::print_occupant_list()
{
    int count = 0;
    while (count < oc_list.size())
    {
        oc_list[count]->print_type();
        count++;
    }
}

// Return the ocupant list
std::vector<Occupant *> &Occupant_List::get_oc_list()
{
    return oc_list;
}
