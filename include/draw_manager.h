#include "texture_manager.h"
#include "occupant_list.h"
#include "wall.h"
#include "coin.h"
#include "pacman.h"
#include "ghost.h"
#include "enum.h"
#include "points.h"
#include "text_manager.h"

#include <iostream>
#include <string>

#ifndef _DRAW_MANAGER_
#define _DRAW_MANAGER_

class Draw_Manager
{
private:
    Texture_Manager texture_manager;
    Text_Manager text_manager{"fonts/ranchos.otf"};

    sf::RenderWindow *window;
    sf::RenderTexture *body;
    sf::RenderTexture *header;

    const int TEXT_HEIGHT = 36;
    int screen_width, body_height, header_height;
    int cell_width, cell_height;
    int nRows, nCols;

public:
    Draw_Manager(sf::RenderWindow &w, sf::RenderTexture &b, sf::RenderTexture &h, int screen_width, int body_height, int header_height, int rows, int cols);
    void draw_board(std::vector<std::vector<Occupant_List>> *board);
    void pacman_animation(Occupant *pacman, int x, int y, int target_x, int target_y, int direction, float tick);
    void draw_pacman(Occupant *pacman, float x, float y, int direction);
    void ghost_animation(Occupant *ghost, std::string name, float tick);
    void draw_ghost(Occupant *ghost, float x, float y, std::string name);
    void handle_rotation(Occupant *occupant, sf::RectangleShape &cell, int direction);
    void draw_score(Points *p);
    void clear_all();
    void draw_all();
    float *lerp(int x1, int y1, int x2, int y2, float tick);
};

#endif