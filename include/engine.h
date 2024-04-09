#include "board.h"
#include "wall.h"
#include "pacman.h"
#include "ghost.h"
#include "enum.h"
#include "navigation.h"
#include "ai.h"
#include "portal.h"
#include "points.h"
#include "life_manager.h"
#include "state_manager.h"

#include <fstream>
#include <vector>

#ifndef _ENGINE_
#define _ENGINE_

class Engine
{
private:
    Pacman *pacman = nullptr;
    Ghost *blinky = nullptr;
    Ghost *pinky = nullptr;
    Ghost *inky = nullptr;
    Ghost *clyde = nullptr;
    Board board;
    Navigation navigation;
    AI ai;
    Points points;
    Life_Manager life_manager{3};
    State_Manager state_manager;

    std::vector<Portal *> portals;

public:
    Engine(std::string map_name);
    Occupant *get_pacman();
    Occupant *get_blinky();
    Occupant *get_pinky();
    Occupant *get_inky();
    Occupant *get_clyde();
    bool check_collision();
    void reset_all_positions();
    Board *get_board();
    Navigation *get_navigation();
    AI *get_ai();
    Points *get_points();
    Life_Manager *get_life_manager();
    State_Manager *get_state_manager();
};

#endif