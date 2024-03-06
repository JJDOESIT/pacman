#include "board.h"
#include "wall.h"
#include "pacman.h"
#include "wall_type.h"
#include "moves.h"
#include "navigation.h"

#include <fstream>

#ifndef _ENGINE_
#define _ENGINE_

class Engine
{
private:
    Pacman *pacman;
    Board board;
    Navigation navigation;

public:
    Engine(std::string map_name);
    Occupant *get_pacman();
    bool *get_possible_moves(Occupant *occupant);
    void move_occupant(Occupant *occupant, int direction);
    Board *get_board();
    Navigation *get_navigation();
};

#endif