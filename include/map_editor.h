#ifndef _MAP_EDITOR_
#define _MAP_EDITOR_

#include "occupant_list.h"
#include "board.h"
#include "occupant.h"
#include "wall.h"
#include "coin.h"
#include "pacman.h"
#include "enum.h"
#include "ghost.h"
#include "config.h"
#include "tile.h"
#include "draw_manager.h"
#include "json.h"
#include "portal.h"

#include <vector>
#include <string>
#include <filesystem>

class Map_Editor
{
private:
    Board board;
    std::vector<Tile> tiles;
    std::string open_map;
    std::vector<Portal *> portals;
    int portal_index;
    int n_in_tile_row;

    void add(Draw_Manager *draw_manager, int row, int col, int type, int specific_type = 0, bool toggled = true);
    float get_mouse_position(int number, int cell_width, int offset = 0);

    void create_config_file(int map_count);
    std::vector<std::string> map_names;

    int selected_tile;
    void reset_selected_tile();

public:
    void create_map(int n_rows, int n_cols);
    Board *get_board();
    void array_to_file();
    void file_to_array(std::string map_name);
    int get_n_rows();
    int get_n_cols();
    std::vector<Tile> *get_tile_set();
    void initilize_tiles(Draw_Manager *draw_manager, int n_in_row);
    void select_tile(float x, float y);
    int get_selected_tile();
    void add_tile(Draw_Manager *draw_manager, float x, float y);
    std::vector<std::string> *map_files();
    void clear_map_files();
    void clear_board();
    int find_int_substring(std::string string);
};

#endif