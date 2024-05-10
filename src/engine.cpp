#include "engine.h"

Engine::~Engine()
{
    if (initilized)
    {
        reset();
    }
}

void Engine::initilize()
{
    if (initilized)
    {
        reset();
    }
    const int ALERT_WIDTH = Config::SCREEN_WIDTH / 2;
    const int ALERT_HEIGHT = Config::BODY_HEIGHT / 8;
    const int ALERT_CHAR_SIZE = 26;
    alert.initilize((Config::SCREEN_WIDTH / 2) - (ALERT_WIDTH / 2), (Config::BODY_HEIGHT / 2) - (ALERT_HEIGHT / 2), ALERT_WIDTH, ALERT_HEIGHT, ALERT_CHAR_SIZE, sf::Color(248, 215, 218), sf::Color(114, 28, 36));
    life_manager = new Life_Manager{Config::N_PACMAN_LIVES};
    state_manager = new State_Manager{ghost_states::ESCAPING};
    navigation = new Navigation{state_manager};
    speed_manager = new Speed_Manager{state_manager, Config::PACMAN_SPEED, Config::GHOST_SPEED};
    ai = new AI{&board, navigation, characters};
    ai->set_target_tiles();
    initilized = true;
}

// Initilize the game engine
void Engine::initilize(std::string map_name)
{
    if (initilized)
    {
        reset();
    }
    const int ALERT_WIDTH = Config::SCREEN_WIDTH / 2;
    const int ALERT_HEIGHT = Config::BODY_HEIGHT / 8;
    const int ALERT_CHAR_SIZE = 26;
    alert.initilize((Config::SCREEN_WIDTH / 2) - (ALERT_WIDTH / 2), (Config::BODY_HEIGHT / 2) - (ALERT_HEIGHT / 2), ALERT_WIDTH, ALERT_HEIGHT, ALERT_CHAR_SIZE, sf::Color(248, 215, 218), sf::Color(114, 28, 36));
    file_to_array(map_name);
    life_manager = new Life_Manager{Config::N_PACMAN_LIVES};
    state_manager = new State_Manager{ghost_states::ESCAPING};
    navigation = new Navigation{state_manager};
    speed_manager = new Speed_Manager{state_manager, Config::PACMAN_SPEED, Config::GHOST_SPEED};
    ai = new AI{&board, navigation, characters};
    ai->set_target_tiles();
    initilized = true;
}

// Reset the game engine
void Engine::reset()
{
    board.clear();
    for (int character = 0; character < 5; character++)
    {
        characters[character] = nullptr;
    }
    portals.clear();
    points.reset();
    state_manager->reset();
    alert.reset();
    delete life_manager;
    delete state_manager;
    delete navigation;
    delete speed_manager;
    delete ai;
    initilized = false;
}

// Fill the board array from the given text file
void Engine::file_to_array(std::string map_name)
{
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
                    row_vector.push_back(Occupant_List(new Wall(current_row, current_col, specific_type)));
                    is_tile = true;
                }
                else if (type == type::COIN)
                {
                    toggled = Json::get_int_from_object(&(tile->value), "toggled");
                    if (toggled)
                    {
                        points.increament_coins();
                    }
                    row_vector.push_back(Occupant_List(new Coin(current_row, current_col, toggled)));
                    is_tile = true;
                }
                else if (type == type::PLAYER)
                {
                    row_vector.push_back(Occupant_List(new Coin(current_row, current_col, false)));
                    characters[characters::game_characters::PACMAN] = new Pacman(current_row, current_col, Config::DEFAULT_PACMAN_DIRECTION);
                    row_vector[current_col].push(characters[characters::game_characters::PACMAN]);
                    is_tile = true;
                }
                else if (type == type::GHOST)
                {
                    row_vector.push_back(Occupant_List(new Coin(current_row, current_col, false)));
                    specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
                    if (specific_type == ghosts_types::BLINKY)
                    {
                        characters[specific_type] = new Ghost(current_row, current_col, Config::DEFAULT_BLINKY_DIRECTION, specific_type);
                    }
                    else if (specific_type == ghosts_types::PINKY)
                    {
                        characters[specific_type] = new Ghost(current_row, current_col, Config::DEFAULT_PINKY_DIRECTION, specific_type);
                    }
                    else if (specific_type == ghosts_types::INKY)
                    {
                        characters[specific_type] = new Ghost(current_row, current_col, Config::DEFAULT_INKY_DIRECTION, specific_type);
                    }
                    else if (specific_type == ghosts_types::CLYDE)
                    {
                        characters[specific_type] = new Ghost(current_row, current_col, Config::DEFAULT_CLYDE_DIRECTION, specific_type);
                    }

                    row_vector[current_col].push(characters[specific_type]);
                    is_tile = true;
                }
                else if (type == type::POWER)
                {
                    specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
                    row_vector.push_back(Occupant_List(new Power(current_row, current_col, specific_type)));
                    is_tile = true;
                }
            }
        }

        // If the tile was not found in the set, it is either the end of the line, end of file, or a portal
        if (!is_tile)
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

    map_editor.set_open_map(map_name);
    points.set_n_initial_coins(points.get_n_coins());
    delete document;

    // If pacman is not placed on the map
    if (!characters[characters::game_characters::PACMAN])
    {
        alert.set_text("Pacman not placed");
        alert.set_toggled(true);
    }
}

// Return a pointer to the speed manager instance
Speed_Manager *Engine::get_speed_manager()
{
    return speed_manager;
}

// Return a pointer to the alert instance
Alert *Engine::get_alert()
{
    return &alert;
}

// Return a pointer to pacman
Occupant *Engine::get_character(int character)
{
    return characters[character];
}

// Return a pointer to the array that holds the characters (blinky, inky, pinky, clyde, and pacman)
Occupant **Engine::get_all_characters()
{
    return characters;
}

// Return whether or not pacman has collided with a ghost
bool Engine::check_collision()
{
    // Loop through each ghost
    for (int i = 0; i < 4; i++)
    {
        // If the ghosts position is equal to pacmans position
        if (characters[i] && characters[i]->get_x_position() == characters[characters::game_characters::PACMAN]->get_x_position() && characters[i]->get_y_position() == characters[characters::game_characters::PACMAN]->get_y_position())
        {
            // And if the ghost has not already been eaten, then a collision has occured
            if (state_manager->get_ghost_state(i) != ghost_states::HEADING_BACK)
            {
                return true;
            }
        }
    }
    return false;
}

// Return a pointer to the board instance
Board *Engine::get_board()
{
    return &board;
}

// Return a pointer to the navigation instance
Navigation *Engine::get_navigation()
{
    return navigation;
}

// Return a pointer to the AI instance
AI *Engine::get_ai()
{
    return ai;
}

// Return whether the engine is initilized or not
bool Engine::is_initilized()
{
    return initilized;
}

// Return a pointer to the points instance
Points *Engine::get_points()
{
    return &points;
}

// Return a pointer to the life manager instance
Life_Manager *Engine::get_life_manager()
{
    return life_manager;
}

// Return a pointer to the state manager instance
State_Manager *Engine::get_state_manager()
{
    return state_manager;
}

// Return a pointer to the map editor instance
Map_Editor *Engine::get_map_editor()
{
    return &map_editor;
}
