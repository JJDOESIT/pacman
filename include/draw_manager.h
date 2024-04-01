#include "texture_manager.h"
#include "occupant_list.h"
#include "wall.h"
#include "coin.h"
#include "pacman.h"
#include "wall_type.h"
#include "moves.h"

#include <iostream>
#include <string>

#ifndef _DRAW_MANAGER_
#define _DRAW_MANAGER_

class Draw_Manager
{
private:
    Texture_Manager texture_manager;
    sf::RenderWindow *window;
    int screen_width, screen_height;
    int cell_width, cell_height;
    int nRows, nCols;

public:
    Draw_Manager(sf::RenderWindow &w, int s_width, int s_height, int rows, int cols);
    void draw_board(std::vector<std::vector<Occupant_List>> *board);
    void draw_pacman(Occupant *pacman);
    void draw_ghost(Occupant *blinky, std::string name);
    void handle_rotation(Occupant *occupant, sf::RectangleShape &cell);
};

#endif