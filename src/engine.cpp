#include "engine.h"

Engine::Engine(std::string map_name)
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

    // Parse the map line by line
    while (std::getline(infile, row, '/'))
    {
        // stlc represents sharp top left corner wall
        if (row == "stlc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::SHARPTOPLEFTCORNER)));
        }
        // strc represents sharp top right corner wall
        else if (row == "strc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::SHARPTOPRIGHTCORNER)));
        }
        // sblc represents sharp bottom left corner wall
        else if (row == "sblc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::SHARPBOTTOMLEFTCORNER)));
        }
        // sbrc represents sharp bottom right corner walls
        else if (row == "sbrc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::SHARPBOTTOMRIGHTCORNER)));
        }
        // trcc represents top right corner connector wall
        else if (row == "trcc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPRIGHTCORNERCONNECTOR)));
        }
        // tlcc represents top left corner connector wall
        else if (row == "tlcc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPLEFTCORNERCONNECTOR)));
        }
        // tlccv represents top left corner connector vertical wall
        else if (row == "tlccv")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPLEFTCORNERCONNECTORVERTICAL)));
        }
        // trccv represents top right corner connector vertical wall
        else if (row == "trccv")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPRIGHTCORNERCONNECTORVERTICAL)));
        }
        // blccv represents bottom left corner connector vertical wall
        else if (row == "blccv")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMLEFTCORNERCONNECTORVERTICAL)));
        }
        // brccv represents bottom right corner connector vertical wall
        else if (row == "brccv")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMRIGHTCORNERCONNECTORVERTICAL)));
        }
        // tlc represents top left corner wall
        else if (row == "tlcd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPLEFTCORNERDOUBLE)));
        }
        // trc represents top right corner wall
        else if (row == "trcd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPRIGHTCORNERDOUBLE)));
        }
        // brc represents bottom right corner wall
        else if (row == "brcd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMRIGHTCORNERDOUBLE)));
        }
        // blc represents bottom left corner wall
        else if (row == "blcd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMLEFTCORNERDOUBLE)));
        }
        // tlcs represents top left single corner wall
        else if (row == "tlcs")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPLEFTCORNERSINGLE)));
        }
        // trc represents top right single corner wall
        else if (row == "trcs")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPRIGHTCORNERSINGLE)));
        }
        // brcs represents bottom right single corner wall
        else if (row == "brcs")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMRIGHTCORNERSINGLE)));
        }
        // blcs represents bottom left single corner wall
        else if (row == "blcs")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMLEFTCORNERSINGLE)));
        }
        // trcsc represents top right corner single connector wall
        else if (row == "trcsc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPRIGHTCORNERSINGLECONNECTOR)));
        }
        // tlcsc represents top left corner single connector wall
        else if (row == "tlcsc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPLEFTCORNERSINGLECONNECTOR)));
        }
        // blcsc represents bottom left corner single connector wall
        else if (row == "blcsc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMLEFTCORNERSINGLECONNECTOR)));
        }
        // brcsc represents bottom right corner single connector wall
        else if (row == "brcsc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMRIGHTCORNERSINGLECONNECTOR)));
        }
        // svl represents straight vertical left double wall
        else if (row == "svld")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTVERTICALLEFTDOUBLE)));
        }
        // svr represents straight vertical right doub;e wall
        else if (row == "svrd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTVERTICALRIGHTDOUBLE)));
        }
        // svml represents straight vertical middle left wall
        else if (row == "svml")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTVERTICALMIDDLELEFT)));
        }
        // svmr represents straight vertical middle right wall
        else if (row == "svmr")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTVERTICALMIDDLERIGHT)));
        }
        // sht represents straight horizontal top double wall
        else if (row == "shtd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTHORIZONTALTOPDOUBLE)));
        }
        // shb represents straight horizontal bottom double wall
        else if (row == "shbd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTHORIZONTALBOTTOMDOUBLE)));
        }
        // shts represents straight horizontal top single wall
        else if (row == "shts")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTHORIZONTALTOPSINGLE)));
        }
        // shbs represents straight horizontal bottom single wall
        else if (row == "shbs")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTHORIZONTALBOTTOMSINGLE)));
        }
        // f represents a filled in wall
        else if (row == "f")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::FILLED)));
        }
        // gate represents a ghost gate
        else if (row == "gate")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::GATE)));
        }
        // c represents a coin
        else if (row == "c")
        {
            row_vector.push_back(Occupant_List(new Coin(current_row, current_col)));
        }
        // s represents an empty space (just a coin toggled off to save space)
        else if (row == "s")
        {
            row_vector.push_back(Occupant_List(new Coin(current_row, current_col, false)));
        }
        // p represents pacman
        else if (row == "p")
        {
            row_vector.push_back(Occupant_List(new Coin(current_row, current_col, false)));
            characters[characters::game_characters::PACMAN] = new Pacman(current_row, current_col, moves::UP);
            row_vector[current_col].push(characters[characters::game_characters::PACMAN]);
        }
        // blinky represents blinky
        else if (row == "blinky")
        {
            row_vector.push_back(Occupant_List(new Coin(current_row, current_col, false)));
            characters[characters::game_characters::BLINKY] = new Ghost(current_row, current_col, moves::LEFT, ghosts_types::BLINKY);
            row_vector[current_col].push(characters[characters::game_characters::BLINKY]);
        }
        // pinky represents pinky
        else if (row == "pinky")
        {
            row_vector.push_back(Occupant_List(new Coin(current_row, current_col, false)));
            characters[characters::game_characters::PINKY] = new Ghost(current_row, current_col, moves::RIGHT, ghosts_types::PINKY);
            row_vector[current_col].push(characters[characters::game_characters::PINKY]);
        }
        // inky represents inky
        else if (row == "inky")
        {
            row_vector.push_back(Occupant_List(new Coin(current_row, current_col, false)));
            characters[characters::game_characters::INKY] = new Ghost(current_row, current_col, moves::UP, ghosts_types::INKY);
            row_vector[current_col].push(characters[characters::game_characters::INKY]);
        }
        // clyde represents clyde
        else if (row == "clyde")
        {
            row_vector.push_back(Occupant_List(new Coin(current_row, current_col, false)));
            characters[characters::game_characters::CLYDE] = new Ghost(current_row, current_col, moves::UP, ghosts_types::CLYDE);
            row_vector[current_col].push(characters[characters::game_characters::CLYDE]);
        }

        // pp represents power pellet
        else if (row == "pp")
        {
            row_vector.push_back(Occupant_List(new Power(current_row, current_col, power_types::POWER_PELLET)));
        }

        // n represents a new line
        else if (row == "n")
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
        current_col++;
    }

    ai = new AI{&board, &navigation, characters};

    // Initilize the ghost's target tiles
    if (characters[characters::game_characters::BLINKY])
    {
        static_cast<Ghost *>(characters[characters::game_characters::BLINKY])->set_target_tile(-3, board.get_cols() - 3);
    }
    if (characters[characters::game_characters::PINKY])
    {
        static_cast<Ghost *>(characters[characters::game_characters::PINKY])->set_target_tile(-3, 2);
    }
    if (characters[characters::game_characters::INKY])
    {
        static_cast<Ghost *>(characters[characters::game_characters::INKY])->set_target_tile(board.get_rows() + 1, board.get_cols());
    }
    if (characters[characters::game_characters::CLYDE])
    {
        static_cast<Ghost *>(characters[characters::game_characters::CLYDE])->set_target_tile(board.get_rows() + 1, 0);
    }

    if (!characters[characters::game_characters::PACMAN])
    {
        std::cout << "Error: Pacman must be placed on the map..." << std::endl;
        exit(1);
    }
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
        if (characters[i]->get_x_position() == characters[characters::game_characters::PACMAN]->get_x_position() && characters[i]->get_y_position() == characters[characters::game_characters::PACMAN]->get_y_position())
        {
            // And if the ghost has not already been eaten, then a collision has occured
            if (state_manager.get_ghost_state(i) != ghost_states::HEADING_BACK)
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
    return &navigation;
}

// Return a pointer to the AI instance
AI *Engine::get_ai()
{
    return ai;
}

// Return a pointer to the points instance
Points *Engine::get_points()
{
    return &points;
}

// Return a pointer to the life manager instance
Life_Manager *Engine::get_life_manager()
{
    return &life_manager;
}

// Return a pointer to the state manager instance
State_Manager *Engine::get_state_manager()
{
    return &state_manager;
}
