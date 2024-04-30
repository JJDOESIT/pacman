#include "map_editor.h"

void Map_Editor::create_map(int n_rows, int n_cols)
{
    Map_Editor::n_rows = n_rows;
    Map_Editor::n_cols = n_cols;

    editing = true;
    selected_tile = -1;

    for (int row = 0; row < n_rows; row++)
    {
        std::vector<Occupant_List> row_vector;
        for (int col = 0; col < n_cols; col++)
        {
            row_vector.push_back(Occupant_List(new Coin(row, col, false)));
        }
        board.push_back(row_vector);
    }

    tiles.push_back(Tile(type::WALL, wall_type::SHARPTOPLEFTCORNER));
    tiles.push_back(Tile(type::WALL, wall_type::SHARPTOPRIGHTCORNER));
    tiles.push_back(Tile(type::WALL, wall_type::SHARPBOTTOMLEFTCORNER));
    tiles.push_back(Tile(type::WALL, wall_type::SHARPBOTTOMRIGHTCORNER));

    tiles.push_back(Tile(type::WALL, wall_type::TOPLEFTCORNERDOUBLE));
    tiles.push_back(Tile(type::WALL, wall_type::TOPRIGHTCORNERDOUBLE));
    tiles.push_back(Tile(type::WALL, wall_type::BOTTOMLEFTCORNERDOUBLE));
    tiles.push_back(Tile(type::WALL, wall_type::BOTTOMRIGHTCORNERDOUBLE));

    tiles.push_back(Tile(type::WALL, wall_type::TOPLEFTCORNERSINGLE));
    tiles.push_back(Tile(type::WALL, wall_type::TOPRIGHTCORNERSINGLE));
    tiles.push_back(Tile(type::WALL, wall_type::BOTTOMLEFTCORNERSINGLE));
    tiles.push_back(Tile(type::WALL, wall_type::BOTTOMRIGHTCORNERSINGLE));

    tiles.push_back(Tile(type::WALL, wall_type::TOPLEFTCORNERSINGLECONNECTOR));
    tiles.push_back(Tile(type::WALL, wall_type::TOPRIGHTCORNERSINGLECONNECTOR));
    tiles.push_back(Tile(type::WALL, wall_type::BOTTOMLEFTCORNERSINGLECONNECTOR));
    tiles.push_back(Tile(type::WALL, wall_type::BOTTOMRIGHTCORNERSINGLECONNECTOR));

    tiles.push_back(Tile(type::WALL, wall_type::TOPLEFTCORNERCONNECTOR));
    tiles.push_back(Tile(type::WALL, wall_type::TOPRIGHTCORNERCONNECTOR));

    tiles.push_back(Tile(type::WALL, wall_type::GATE));

    tiles.push_back(Tile(type::WALL, wall_type::TOPLEFTCORNERCONNECTORVERTICAL));
    tiles.push_back(Tile(type::WALL, wall_type::TOPRIGHTCORNERCONNECTORVERTICAL));

    tiles.push_back(Tile(type::WALL, wall_type::FILLED));

    tiles.push_back(Tile(type::WALL, wall_type::BOTTOMLEFTCORNERCONNECTORVERTICAL));
    tiles.push_back(Tile(type::WALL, wall_type::BOTTOMRIGHTCORNERCONNECTORVERTICAL));

    tiles.push_back(Tile(type::WALL, wall_type::STRAIGHTHORIZONTALBOTTOMSINGLE));
    tiles.push_back(Tile(type::WALL, wall_type::STRAIGHTHORIZONTALBOTTOMDOUBLE));

    tiles.push_back(Tile(type::WALL, wall_type::STRAIGHTHORIZONTALTOPDOUBLE));
    tiles.push_back(Tile(type::WALL, wall_type::STRAIGHTHORIZONTALTOPSINGLE));

    tiles.push_back(Tile(type::WALL, wall_type::STRAIGHTVERTICALLEFTDOUBLE));
    tiles.push_back(Tile(type::WALL, wall_type::STRAIGHTVERTICALRIGHTDOUBLE));

    tiles.push_back(Tile(type::WALL, wall_type::STRAIGHTVERTICALMIDDLELEFT));
    tiles.push_back(Tile(type::WALL, wall_type::STRAIGHTVERTICALMIDDLERIGHT));

    tiles.push_back(Tile(type::PLAYER));
    tiles.push_back(Tile(type::GHOST, ghosts_types::BLINKY));
    tiles.push_back(Tile(type::GHOST, ghosts_types::PINKY));
    tiles.push_back(Tile(type::GHOST, ghosts_types::INKY));
    tiles.push_back(Tile(type::GHOST, ghosts_types::CLYDE));

    tiles.push_back(Tile(type::POWER, power_types::POWER_PELLET));
}

// Return a pointer to the board
std::vector<std::vector<Occupant_List>> *Map_Editor::get_board()
{
    return &board;
}

// Given an x, y, and cell_width, return the mouse position in a relative index form
float Map_Editor::get_mouse_position(int number, int cell_width, int offset)
{
    number -= offset;
    int distance = number % cell_width;

    number -= distance;
    return number / cell_width;
}

// Convert the array to a map text file
void Map_Editor::array_to_file()
{

    int map_count = Json::get_int(Config::JSON_DIR + "config" + ".json", "map_count");

    // Create a new file
    std::ofstream ofstream(Config::MAP_DIR + "map" + std::to_string(map_count) + ".txt");

    // Check if the file was created
    if (!ofstream)
    {
        exit(1);
    }

    // Increament the map count by one
    Json::set_int(Config::JSON_DIR + "config" + ".json", "map_count", ++map_count);

    int type, specific_type, toggle;
    std::string string_type;

    // Loop through the board
    for (int row = 0; row < n_rows; row++)
    {
        for (int col = 0; col < n_cols; col++)
        {
            // Get the type of the occupant
            type = board[row][col].get_oc_list()[0]->get_type();

            if (type == type::WALL)
            {
                specific_type = static_cast<Wall *>(board[row][col].get_oc_list()[0])->get_wall_type();
                string_type = Json::get_string(Config::JSON_DIR + "wall_strings" + ".json", std::to_string(specific_type));
            }
            else if (type == type::GHOST)
            {
                specific_type = static_cast<Ghost *>(board[row][col].get_oc_list()[0])->get_type();
                string_type = Json::get_string(Config::JSON_DIR + "ghost_strings" + ".json", std::to_string(specific_type));
            }
            else if (type == type::COIN)
            {
                toggle = static_cast<Coin *>(board[row][col].get_oc_list()[0])->get_toggled();
                string_type = Json::get_string(Config::JSON_DIR + "coin_strings" + ".json", std::to_string(toggle));
            }
            else if (type == type::POWER)
            {
                specific_type = static_cast<Power *>(board[row][col].get_oc_list()[0])->get_type();
                string_type = Json::get_string(Config::JSON_DIR + "power_strings" + ".json", std::to_string(specific_type));
            }
            else if (type == type::PLAYER)
            {
                string_type = Json::get_string(Config::JSON_DIR + "pacman_strings" + ".json", "0");
            }
            ofstream << string_type + "/";
        }
        row != n_rows - 1 ? ofstream << "n/"
                                     << "\n"
                          : ofstream << "e/";
    }
}

// Add a specific occupant to the board
void Map_Editor::add(int row, int col, int type, int specific_type)
{
    // Clear the occupant list
    board[row][col].clear();

    Occupant *occupant;
    if (type == type::WALL)
    {
        occupant = new Wall(row, col, specific_type);
    }
    else if (type == type::GHOST)
    {
        if (specific_type == ghosts_types::BLINKY)
        {
            occupant = new Ghost(row, col, Config::DEFAULT_BLINKY_DIRECTION, specific_type);
        }
        else if (specific_type == ghosts_types::PINKY)
        {
            occupant = new Ghost(row, col, Config::DEFAULT_PINKY_DIRECTION, specific_type);
        }
        else if (specific_type == ghosts_types::INKY)
        {
            occupant = new Ghost(row, col, Config::DEFAULT_INKY_DIRECTION, specific_type);
        }
        else if (specific_type == ghosts_types::CLYDE)
        {
            occupant = new Ghost(row, col, Config::DEFAULT_CLYDE_DIRECTION, specific_type);
        }
    }
    else if (type == type::COIN)
    {
        occupant = new Coin(row, col, specific_type);
    }
    else if (type == type::PLAYER)
    {
        occupant = new Pacman(row, col, Config::DEFAULT_PACMAN_DIRECTION);
    }
    else if (type == type::POWER)
    {
        occupant = new Power(row, col, specific_type);
    }

    // Push the new occupant onto the board
    board[row][col].push(occupant);
}

// Return the number of rows
int Map_Editor::get_n_rows()
{
    return n_rows;
}

// Return the number of cols
int Map_Editor::get_n_cols()
{
    return n_cols;
}

// Return a pointer to the tile set
std::vector<Tile> *Map_Editor::get_tile_set()
{
    return &tiles;
}

// Initilize the positions of the selectable tiles
void Map_Editor::initilize_tiles(Draw_Manager *draw_manager, int n_in_row)
{
    float cell_width = (Config::SCREEN_WIDTH - (n_in_row * (Config::BORDER_OUTLINE_THICKNESS * 2)) - (n_in_row - 1)) / n_in_row;
    float cell_height = cell_width;

    n_in_tile_row = n_in_row;

    int row = 0;
    for (int col = 0; col < tiles.size(); col++)
    {
        if (col % n_in_row == 0)
        {
            row++;
        }
        tiles[col].get_rect().setSize(sf::Vector2f(cell_width, cell_height));
        tiles[col].get_rect().setPosition(sf::Vector2f(((col % n_in_row) * (Config::SCREEN_WIDTH / n_in_row)) + Config::BORDER_OUTLINE_THICKNESS, (row * (Config::SCREEN_WIDTH / n_in_row)) + Config::BORDER_OUTLINE_THICKNESS));
        tiles[col].get_rect().setOutlineThickness(Config::BORDER_OUTLINE_THICKNESS);
        tiles[col].get_rect().setOutlineColor(sf::Color::White);
        draw_manager->set_texture((tiles[col].get_rect()), tiles[col].get_type(), tiles[col].get_specific_type(), tiles[col].get_toggled());
    }
}

// Toggle the state to be editing or not editing
void Map_Editor::toggle_editing(bool editing)
{
    Map_Editor::editing = editing;
}

// Return whether the user is creating a map or not
bool Map_Editor::is_editing()
{
    return editing;
}

// Select a tile given relative coords to the footer window
void Map_Editor::select_tile(float x, float y)
{
    if (selected_tile != -1)
    {
        tiles[selected_tile].get_rect().setOutlineColor(sf::Color::White);
    }
    float cell_width = Config::SCREEN_WIDTH / n_in_tile_row;
    x = get_mouse_position(x, cell_width);
    y = get_mouse_position(y, cell_width, cell_width);
    selected_tile = n_in_tile_row * y + x;
    tiles[selected_tile].get_rect().setOutlineColor(sf::Color::Red);
}

void Map_Editor::add_tile(float x, float y)
{
    if (selected_tile != -1)
    {
        float cell_width = Config::SCREEN_WIDTH / n_cols;
        float cell_height = Config::BODY_HEIGHT / n_rows;
        x = get_mouse_position(x, cell_width);
        y = get_mouse_position(y, cell_height);
        add(y, x, tiles[selected_tile].get_type(), tiles[selected_tile].get_specific_type());
    }
}
