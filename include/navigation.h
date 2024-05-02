#include "occupant.h"
#include "board.h"
#include "enum.h"
#include "wall.h"
#include "pacman.h"
#include "ghost.h"
#include "portal.h"
#include "points.h"
#include "power.h"
#include "linear_directions.h"
#include "state_manager.h"
#include "draw_manager.h"

#ifndef _NAVIGATION_
#define _NAVIGATION_

class Navigation
{
private:
    State_Manager *state_manager;

    void reset_position(Board *board, Occupant *occupant);

public:
    Navigation(State_Manager *sm);
    bool *get_possible_moves(Occupant *occupant, Board *board);
    void move_occupant(Draw_Manager *draw_manager, Occupant *occupant, Board *board, int direction, Points *points = nullptr, int *powerup = nullptr);
    void move(Draw_Manager *draw_manager, Occupant *occupant, Board *board, int direction, Points *points = nullptr, int *powerup = nullptr);

    void reset_all_characters(Board *board, Occupant **characters);
};

#endif