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
#include "power.h"
#include "map_editor.h"

#include <fstream>
#include <vector>

#ifndef _ENGINE_
#define _ENGINE_

class Engine
{
private:
    Occupant *characters[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    Board board;
    State_Manager *state_manager;
    Navigation *navigation;
    AI *ai;
    Points points;
    Life_Manager life_manager{3};
    std::vector<Portal *> portals;
    Map_Editor map_editor;

public:
    Engine(std::string map_name);
    ~Engine();
    Occupant *get_character(int character);
    Occupant **get_all_characters();
    bool check_collision();
    Board *get_board();
    Navigation *get_navigation();
    AI *get_ai();
    Points *get_points();
    Life_Manager *get_life_manager();
    State_Manager *get_state_manager();
    Map_Editor *get_map_editor();
};

#endif