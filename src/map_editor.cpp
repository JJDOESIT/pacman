#include "map_editor.h"

// Create a map a given size
void Map_Editor::create_map(int n_rows, int n_cols)
{
    clear_board();
    reset_selected_tile();

    open_map = "";

    board.set_rows(n_rows);
    board.set_cols(n_cols);

    selected_tile = -1;

    for (int row = 0; row < n_rows; row++)
    {
        std::vector<Occupant_List> row_vector;
        for (int col = 0; col < n_cols; col++)
        {
            row_vector.push_back(Occupant_List(new Coin(row, col, false)));
        }
        (*board.get_board()).push_back(row_vector);
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
Board *Map_Editor::get_board()
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

// Initilize default config file
void Map_Editor::create_config_file(int map_count)
{
    rapidjson::Document *document = Json::get_document(Config::JSON_DIR + "default_config.json");
    rapidjson::Value *config_list = Json::get_object(document, "config");

    // Create a new file
    std::ofstream ofstream("config/config" + std::to_string(map_count) + ".txt");

    // Check if the file was created
    if (!ofstream)
    {
        std::cout << "Error: Cannot create file ..." << std::endl;
        exit(1);
    }

    int int_value;
    int array_value[2];
    std::string string_value;
    for (rapidjson::Value::MemberIterator item = config_list->MemberBegin(); item != config_list->MemberEnd(); item++)
    {
        if (item->value.IsInt())
        {
            int_value = item->value.GetInt();
            ofstream << item->name.GetString() << "=" << int_value << '\n';
        }
        else if (item->value.IsArray())
        {
            array_value[0] = item->value.GetArray()[0].GetInt();
            array_value[1] = item->value.GetArray()[1].GetInt();
            ofstream << item->name.GetString() << "=" << array_value[0] << "," << array_value[1] << '\n';
        }
        else if (item->value.IsString())
        {
            string_value = item->value.GetString();
            ofstream << item->name.GetString() << "=" << string_value << '\n';
        }
    }

    ofstream.close();
}

// Clear all selected tiles
void Map_Editor::reset_selected_tile()
{
    selected_tile = -1;
}

// Convert the array to a map text file
void Map_Editor::array_to_file()
{
    int map_count = 0;
    bool found_new_name = false;

    rapidjson::Document *document = Json::get_document(Config::JSON_DIR + "map_count.json");
    rapidjson::Value *value = Json::get_object(document, "taken_maps");

    while (!found_new_name)
    {
        found_new_name = true;
        for (rapidjson::SizeType i = 0; i < value->Size(); i++)
        {
            if (map_count == (*value)[i].GetInt())
            {
                found_new_name = false;
            }
        }
        if (!found_new_name)
        {
            map_count++;
        }
    }

    std::ofstream ofstream;

    // Create a new file
    if (open_map.length() == 0)
    {
        ofstream.open(Config::MAP_DIR + "map" + std::to_string(map_count) + ".txt");
    }
    else
    {
        ofstream.open(open_map, std::ios::out | std::ios::trunc);
    }

    // Check if the file was created
    if (!ofstream)
    {
        std::cout << "Error: Cannot create/open file ..." << std::endl;
        delete document;
        exit(1);
    }

    // Increament the map count by one and create a config file
    if (open_map.length() == 0)
    {
        // create_config_file(map_count);
        Json::add_int_to_array(Config::JSON_DIR + "map_count.json", document, value, map_count);
    }

    delete document;

    int board_type, board_specific_type, board_toggled;
    int tile_type, tile_specific_type, tile_toggled;
    portal_index = 0;

    document = Json::get_document(Config::JSON_DIR + "tiles.json");
    rapidjson::Value *tile_list = Json::get_object(document, "tiles");

    for (int row = 0; row < board.get_rows(); row++)
    {
        for (int col = 0; col < board.get_cols(); col++)
        {
            // Get the type of the occupant
            board_type = (*board.get_board())[row][col].get_oc_list()[0]->get_type();
            if (board_type == type::WALL)
            {
                board_specific_type = static_cast<Wall *>((*board.get_board())[row][col].get_oc_list()[0])->get_wall_type();
            }
            else if (board_type == type::GHOST)
            {
                board_specific_type = static_cast<Ghost *>((*board.get_board())[row][col].get_oc_list()[0])->get_type();
            }
            else if (board_type == type::COIN)
            {
                board_toggled = static_cast<Coin *>((*board.get_board())[row][col].get_oc_list()[0])->get_toggled();
            }
            else if (board_type == type::POWER)
            {
                board_specific_type = static_cast<Power *>((*board.get_board())[row][col].get_oc_list()[0])->get_type();
            }
            else if (board_type == type::PORTAL)
            {
                ofstream << std::to_string(static_cast<Portal *>((*board.get_board())[row][col].find_occupant(type::PORTAL))->get_direction()) + std::to_string(static_cast<Portal *>((*board.get_board())[row][col].find_occupant(type::PORTAL))->get_id()) + "/";
            }

            for (rapidjson::Value::MemberIterator tile = tile_list->MemberBegin(); tile != tile_list->MemberEnd(); tile++)
            {
                tile_type = Json::get_int_from_object(&(tile->value), "type");
                if (tile_type == type::WALL)
                {
                    tile_specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
                    if (tile_specific_type == board_specific_type && tile_type == board_type)
                    {
                        ofstream << std::string(tile->name.GetString()) + "/";
                    }
                }
                else if (tile_type == type::COIN)
                {
                    tile_toggled = Json::get_int_from_object(&(tile->value), "toggled");
                    if (tile_toggled == board_toggled && tile_type == board_type)
                    {
                        ofstream << std::string(tile->name.GetString()) + "/";
                    }
                }
                else if (tile_type == type::PLAYER)
                {
                    if (tile_type == board_type)
                    {
                        ofstream << std::string(tile->name.GetString()) + "/";
                    }
                }
                else if (tile_type == type::GHOST)
                {
                    tile_specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
                    if (tile_specific_type == board_specific_type && tile_type == board_type)
                    {
                        ofstream << std::string(tile->name.GetString()) + "/";
                    }
                }
                else if (tile_type == type::POWER)
                {
                    tile_specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
                    if (tile_specific_type == board_specific_type && tile_type == board_type)
                    {
                        ofstream << std::string(tile->name.GetString()) + "/";
                    }
                }
            }
        }
        row != board.get_rows() - 1 ? ofstream << "n/"
                                               << "\n"
                                    : ofstream << "e/";
    }
    delete document;
    ofstream.close();
}

// Read a given map file into the board editor
void Map_Editor::file_to_array(std::string map_name)
{
    clear_board();
    reset_selected_tile();

    std::ifstream infile;

    infile.open(map_name);

    // If the file cannot be found
    if (!infile)
    {
        std::cout << "Map file not found ..." << std::endl;
        exit(1);
    }

    std::string row;
    int current_row = 0;
    int current_col = 0;
    std::vector<Occupant_List> row_vector;

    rapidjson::Document *document = Json::get_document(Config::JSON_DIR + "tiles.json");
    rapidjson::Value *tile_list = Json::get_object(document, "tiles");

    Occupant *occupant;
    int type, specific_type, toggled;
    bool is_tile;

    // Parse the map line by line
    while (std::getline(infile, row, '/'))
    {
        is_tile = false;

        // Loop through the tile set
        for (rapidjson::Value::MemberIterator tile = tile_list->MemberBegin(); tile != tile_list->MemberEnd(); tile++)
        {
            //  If the current tile is in the tile set
            if (row == tile->name.GetString())
            {
                // Fetch the initial type of the tile (WALL, GHOST, COIN, PLAYER, etc)
                type = Json::get_int_from_object(&(tile->value), "type");

                if (type == type::WALL)
                {
                    specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
                    occupant = new Wall(current_row, current_col, specific_type);
                    is_tile = true;
                }
                else if (type == type::COIN)
                {
                    toggled = Json::get_int_from_object(&(tile->value), "toggled");
                    occupant = new Coin(current_row, current_col, toggled);
                    is_tile = true;
                }
                else if (type == type::PLAYER)
                {
                    occupant = new Pacman(current_row, current_col, moves::RIGHT);
                    is_tile = true;
                }
                else if (type == type::GHOST)
                {
                    specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
                    occupant = new Ghost(current_row, current_col, moves::RIGHT, specific_type);
                    is_tile = true;
                }
                else if (type == type::POWER)
                {
                    specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
                    occupant = new Power(current_row, current_col, specific_type);
                    is_tile = true;
                }
            }
        }

        // If the tile was not found in the set, it is either the end of the line, end of file, or a portal
        if (is_tile)
        {
            row_vector.push_back(Occupant_List(occupant));
        }
        else
        {
            // n represents a new line
            if (row == "n")
            {
                current_row++;
                current_col = -1;
                (*board.get_board()).push_back(row_vector);
                row_vector.clear();
                infile.ignore();
            }
            // e represents the end of the map file
            else if (row == "e")
            {
                board.set_rows(current_row + 1);
                board.set_cols(current_col);
                (*board.get_board()).push_back(row_vector);
            }
            // a number represents a portal
            else if (std::stoi(row) >= 0 && std::stoi(row) <= 39)
            {
                int direction, subtract;
                if (std::stoi(row) <= 9)
                {
                    direction = moves::UP;
                    subtract = 0;
                }
                else if (std::stoi(row) <= 19)
                {
                    direction = moves::RIGHT;
                    subtract = 10;
                }
                else if (std::stoi(row) <= 29)
                {
                    direction = moves::DOWN;
                    subtract = 20;
                }
                else
                {
                    direction = moves::LEFT;
                    subtract = 30;
                }

                Portal *portal = new Portal(current_row, current_col, direction, std::stoi(row) - subtract);
                row_vector.push_back(Occupant_List(portal));

                bool found_link = false;

                for (int i = 0; i < portals.size(); i++)
                {
                    if (portals[i]->get_id() == portal->get_id())
                    {
                        portals[i]->set_link(portal);
                        portal->set_link(portals[i]);
                        portals.erase(portals.begin() + i);
                        found_link = true;
                    }
                }

                if (!found_link)
                {
                    portals.push_back(portal);
                }
            }
        }

        current_col++;
    }
    delete document;
    infile.close();
    open_map = map_name;
}

// Find an integer substring in a given string
int Map_Editor::find_int_substring(std::string string)
{
    int index = 0;
    std::string intStr;

    // Find the start of the integer substring
    while (index < string.size() && !std::isdigit(string[index]))
    {
        index++;
    }

    // Build the integer substring
    while (index < string.size() && std::isdigit(string[index]))
    {
        intStr += string[index];
        index++;
    }

    // Convert the substring to an integer
    int result = std::stoi(intStr);

    return result;
}

// Add a specific occupant to the board
void Map_Editor::add(Draw_Manager *draw_manager, int row, int col, int type, int specific_type)
{
    // Clear the occupant list
    (*board.get_board())[row][col].clear();

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

    // Set the texture of the newly created occupant
    draw_manager->set_texture(*occupant->get_cell(), type, specific_type);

    // Push the new occupant onto the board
    (*board.get_board())[row][col].push(occupant);
}

// Return the number of rows
int Map_Editor::get_n_rows()
{
    return board.get_rows();
}

// Return the number of cols
int Map_Editor::get_n_cols()
{
    return board.get_cols();
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

// Select a tile given relative coords to the footer window
void Map_Editor::select_tile(float x, float y)
{
    float cell_width = Config::SCREEN_WIDTH / n_in_tile_row;
    x = get_mouse_position(x, cell_width);
    y = get_mouse_position(y, cell_width, cell_width);
    selected_tile = n_in_tile_row * y + x;
}

// Add a tile to a given cell based on mouse click
void Map_Editor::add_tile(Draw_Manager *draw_manager, float x, float y)
{
    if (selected_tile != -1)
    {
        float cell_width = Config::SCREEN_WIDTH / board.get_cols();
        float cell_height = Config::BODY_HEIGHT / board.get_rows();
        x = get_mouse_position(x, cell_width);
        y = get_mouse_position(y, cell_height);
        add(draw_manager, y, x, tiles[selected_tile].get_type(), tiles[selected_tile].get_specific_type());
    }
}

// Return a new vector containing all files in the MAP_DIR
std::vector<std::string> *Map_Editor::map_files()
{
    for (const auto &entry : std::filesystem::directory_iterator(Config::MAP_DIR))
    {
        map_names.push_back(entry.path().filename().string());
    }
    return &map_names;
}

// Return the selected tile
int Map_Editor::get_selected_tile()
{
    return selected_tile;
}

// Clear the map files vector
void Map_Editor::clear_map_files()
{
    map_names.clear();
}

// Clear the map board
void Map_Editor::clear_board()
{
    board.clear();
}
