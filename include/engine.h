#include "board.h"
#include "wall.h"
#include "pacman.h"
#include "ghost.h"
#include "wall_type.h"
#include "moves.h"
#include "navigation.h"
#include "ai.h"
#include "portal.h"

#include <fstream>
#include <vector>

#ifndef _ENGINE_
#define _ENGINE_

class Engine
{
private:
    Pacman *pacman;
    Ghost *blinky;
    Ghost *pinky;
    Ghost *inky;
    Ghost *clyde;
    Board board;
    Navigation navigation;
    AI ai;
    std::vector<Portal *> portals;

public:
    Engine(std::string map_name);
    Occupant *get_pacman();
    Occupant *get_blinky();
    Occupant *get_pinky();
    Occupant *get_inky();
    Occupant *get_clyde();
    bool *get_possible_moves(Occupant *occupant);
    void move_occupant(Occupant *occupant, int direction);
    Board *get_board();
    Navigation *get_navigation();
    AI *get_ai();
};

#endif