#include "occupant.h"
#include "board.h"
#include "moves.h"
#include "pacman.h"

#ifndef _NAVIGATION_
#define _NAVIGATION_

class Navigation
{
public:
    bool *get_possible_moves(Occupant *occupant, Board *board);
    void move_occupant(Occupant *occupant, Board *board, int direction);
};

#endif