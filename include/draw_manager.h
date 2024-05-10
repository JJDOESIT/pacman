#ifndef _DRAW_MANAGER_
#define _DRAW_MANAGER_

#include "board.h"
#include "texture_manager.h"
#include "occupant_list.h"
#include "wall.h"
#include "coin.h"
#include "pacman.h"
#include "ghost.h"
#include "enum.h"
#include "points.h"
#include "text_manager.h"
#include "power.h"
#include "state_manager.h"
#include "speed_manager.h"
#include "tile.h"
#include "config.h"
#include "json.h"
#include "button.h"
#include "input.h"
#include "alert.h"

#include <iostream>
#include <string>

class Draw_Manager
{
private:
    Texture_Manager texture_manager;

    sf::RenderWindow *window;
    sf::RenderTexture *header;
    sf::RenderTexture *body;
    sf::RenderTexture *footer;

    const int TEXT_HEIGHT = 36;

    float *lerp(int x1, int y1, int x2, int y2, float tick);
    void handle_rotation(Occupant *occupant, sf::RectangleShape &cell, int direction, int cell_width, int cell_height);
    void draw_pacman(Occupant *pacman, float x, float y, int direction, int cell_width, int cell_height);
    void ghost_animation(State_Manager *state_manager, Occupant *ghost, std::string name, float tick, int cell_width, int cell_height);
    void draw_ghost(Occupant *ghost, float x, float y, std::string name, int cell_width, int cell_height);
    void draw_frightened_ghost(Occupant *ghost, float x, float y, int cell_width, int cell_height);
    void draw_ghost_eyes(Occupant *ghost, float x, float y, int cell_width, int cell_height);

public:
    Draw_Manager(sf::RenderWindow &w, sf::RenderTexture &h, sf::RenderTexture &b, sf::RenderTexture &f);

    void initilize_textures(Board *b);
    void draw_board(Board *b, bool outline = false);
    void pacman_animation(Occupant *pacman, int x, int y, int target_x, int target_y, int direction, float tick, int n_rows, int n_cols);

    void draw_all_ghost_animation(State_Manager *state_manager, Occupant **characters, Speed_Manager *speed_manager, int n_rows, int n_cols);

    void draw_all_ghosts(Occupant **characters, int n_rows, int n_cols);

    void draw_score(Points *p);

    void draw_tiles(std::vector<Tile> *tiles, int selected_tile);

    void set_texture(sf::RectangleShape &cell, int type, int specific_type, bool toggled = true);

    void draw_buttons(std::vector<Button *> *buttons, int texture_surface);

    void draw_inputs(std::vector<Input *> *inputs, int selected_input, int texture_surface);

    void draw_lives(int n_pacman_lives);

    void draw_alert(Alert *alert);

    void clear_all();
    void draw_all();
};

#endif