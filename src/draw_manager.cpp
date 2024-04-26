#include "draw_manager.h"

Draw_Manager::Draw_Manager(sf::RenderWindow &w, sf::RenderTexture &h, sf::RenderTexture &b, sf::RenderTexture &f, int rows, int cols)
{
    window = &w;
    header = &h;
    body = &b;
    footer = &f;
    nRows = rows;
    nCols = cols;
}

// Handle the rotation of a sprite given a direction
void Draw_Manager::handle_rotation(Occupant *occupant, sf::RectangleShape &cell, int direction, int cell_width, int cell_height)
{
    switch (direction)
    {
    case (moves::UP):
        cell.setSize(sf::Vector2f(cell_height, cell_width));
        cell.setOrigin(sf::Vector2f(sf::Vector2f(cell.getSize().x, 0)));
        cell.rotate(-90);
        break;
    case (moves::RIGHT):
        break;
    case (moves::DOWN):
        cell.setSize(sf::Vector2f(cell_height, cell_width));
        cell.setOrigin(sf::Vector2f(sf::Vector2f(0, cell.getSize().y)));
        cell.rotate(90);
        break;
    case (moves::LEFT):
        cell.setOrigin(sf::Vector2f(sf::Vector2f(cell.getSize().x, 0)));
        cell.setScale(sf::Vector2f(-1, 1));
        break;
    }
}

// Draw the score to the header
void Draw_Manager::draw_score(Points *p)
{
    p->stringify();
    text_manager.set_text(p->get_points_string(), TEXT_HEIGHT, sf::Color::White);
    sf::Text text = text_manager.get_text();
    text.setPosition(sf::Vector2f(10, (HEADER_HEIGHT / 2) - (TEXT_HEIGHT / 2)));
    header->draw(text);
}

// Draw the tile set for the map editor
void Draw_Manager::draw_tiles(std::vector<Tile> *tiles)
{

    for (int i = 0; i < tiles->size(); i++)
    {
        if ((*tiles)[i].get_is_selected())
        {
            (*tiles)[i].get_rect().setFillColor(sf::Color(255, 255, 255, 128));
        }
        footer->draw((*tiles)[i].get_rect());
    }
}

// Clear the display
void Draw_Manager::clear_all()
{
    window->clear();
    header->clear();
    body->clear();
    footer->clear();
}

// Draw the display
void Draw_Manager::draw_all()
{
    header->display();
    body->display();
    footer->display();
    sf::Sprite header_texture(header->getTexture());
    sf::Sprite body_texture(body->getTexture());
    sf::Sprite footer_texture(footer->getTexture());
    body_texture.setPosition(0, HEADER_HEIGHT);
    footer_texture.setPosition(0, HEADER_HEIGHT + BODY_HEIGHT);
    window->draw(header_texture);
    window->draw(body_texture);
    window->draw(footer_texture);
    window->display();
}

// Lerp between two given points and a tick
float *Draw_Manager::lerp(int x1, int y1, int x2, int y2, float tick)
{
    float x = x1 + tick * (x2 - x1);
    float y = y1 + tick * (y2 - y1);

    float *point = new float[2];
    point[0] = x;
    point[1] = y;

    return point;
}

// Given a type, subtype, and state, set the according texture to the cell
void Draw_Manager::set_texture(sf::RectangleShape &cell, int type, int specific_type, bool toggled)
{
    if (type == type::WALL)
    {
        if (specific_type == wall_type::SHARPTOPLEFTCORNER)
        {
            cell.setTexture(texture_manager.get_texture("stlc"));
        }
        else if (specific_type == wall_type::SHARPTOPRIGHTCORNER)
        {
            cell.setTexture(texture_manager.get_texture("strc"));
        }
        else if (specific_type == wall_type::SHARPBOTTOMLEFTCORNER)
        {
            cell.setTexture(texture_manager.get_texture("sblc"));
        }
        else if (specific_type == wall_type::SHARPBOTTOMRIGHTCORNER)
        {
            cell.setTexture(texture_manager.get_texture("sbrc"));
        }
        else if (specific_type == wall_type::TOPRIGHTCORNERCONNECTOR)
        {
            cell.setTexture(texture_manager.get_texture("trcc"));
        }
        else if (specific_type == wall_type::TOPLEFTCORNERCONNECTOR)
        {
            cell.setTexture(texture_manager.get_texture("tlcc"));
        }
        else if (specific_type == wall_type::TOPLEFTCORNERCONNECTORVERTICAL)
        {
            cell.setTexture(texture_manager.get_texture("tlccv"));
        }
        else if (specific_type == wall_type::TOPRIGHTCORNERCONNECTORVERTICAL)
        {
            cell.setTexture(texture_manager.get_texture("trccv"));
        }
        else if (specific_type == wall_type::BOTTOMLEFTCORNERCONNECTORVERTICAL)
        {
            cell.setTexture(texture_manager.get_texture("blccv"));
        }
        else if (specific_type == wall_type::BOTTOMRIGHTCORNERCONNECTORVERTICAL)
        {
            cell.setTexture(texture_manager.get_texture("brccv"));
        }
        else if (specific_type == wall_type::TOPLEFTCORNERDOUBLE)
        {
            cell.setTexture(texture_manager.get_texture("tlcd"));
        }
        else if (specific_type == wall_type::TOPRIGHTCORNERDOUBLE)
        {
            cell.setTexture(texture_manager.get_texture("trcd"));
        }
        else if (specific_type == wall_type::BOTTOMRIGHTCORNERDOUBLE)
        {
            cell.setTexture(texture_manager.get_texture("brcd"));
        }
        else if (specific_type == wall_type::BOTTOMLEFTCORNERDOUBLE)
        {
            cell.setTexture(texture_manager.get_texture("blcd"));
        }
        if (specific_type == wall_type::TOPLEFTCORNERSINGLE)
        {
            cell.setTexture(texture_manager.get_texture("tlcs"));
        }
        else if (specific_type == wall_type::TOPRIGHTCORNERSINGLE)
        {
            cell.setTexture(texture_manager.get_texture("trcs"));
        }
        else if (specific_type == wall_type::BOTTOMRIGHTCORNERSINGLE)
        {
            cell.setTexture(texture_manager.get_texture("brcs"));
        }
        else if (specific_type == wall_type::BOTTOMLEFTCORNERSINGLE)
        {
            cell.setTexture(texture_manager.get_texture("blcs"));
        }
        else if (specific_type == wall_type::TOPLEFTCORNERSINGLECONNECTOR)
        {
            cell.setTexture(texture_manager.get_texture("tlcsc"));
        }
        else if (specific_type == wall_type::TOPRIGHTCORNERSINGLECONNECTOR)
        {
            cell.setTexture(texture_manager.get_texture("trcsc"));
        }
        else if (specific_type == wall_type::BOTTOMRIGHTCORNERSINGLECONNECTOR)
        {
            cell.setTexture(texture_manager.get_texture("brcsc"));
        }
        else if (specific_type == wall_type::BOTTOMLEFTCORNERSINGLECONNECTOR)
        {
            cell.setTexture(texture_manager.get_texture("blcsc"));
        }
        else if (specific_type == wall_type::STRAIGHTVERTICALLEFTDOUBLE)
        {
            cell.setTexture(texture_manager.get_texture("svld"));
        }
        else if (specific_type == wall_type::STRAIGHTVERTICALRIGHTDOUBLE)
        {
            cell.setTexture(texture_manager.get_texture("svrd"));
        }
        else if (specific_type == wall_type::STRAIGHTVERTICALMIDDLELEFT)
        {
            cell.setTexture(texture_manager.get_texture("svml"));
        }
        else if (specific_type == wall_type::STRAIGHTVERTICALMIDDLERIGHT)
        {
            cell.setTexture(texture_manager.get_texture("svmr"));
        }
        else if (specific_type == wall_type::STRAIGHTHORIZONTALTOPDOUBLE)
        {
            cell.setTexture(texture_manager.get_texture("shtd"));
        }
        else if (specific_type == wall_type::STRAIGHTHORIZONTALBOTTOMDOUBLE)
        {
            cell.setTexture(texture_manager.get_texture("shbd"));
        }
        else if (specific_type == wall_type::STRAIGHTHORIZONTALTOPSINGLE)
        {
            cell.setTexture(texture_manager.get_texture("shts"));
        }
        else if (specific_type == wall_type::STRAIGHTHORIZONTALBOTTOMSINGLE)
        {
            cell.setTexture(texture_manager.get_texture("shbs"));
        }
        else if (specific_type == wall_type::FILLED)
        {
            cell.setTexture(texture_manager.get_texture("f"));
        }
        else if (specific_type == wall_type::GATE)
        {
            cell.setTexture(texture_manager.get_texture("f"));
        }
    }
    else if (type == type::COIN)
    {
        if (toggled)
        {
            cell.setTexture(texture_manager.get_texture("c"));
        }
        else
        {
            cell.setTexture(texture_manager.get_texture("f"));
        }
    }
    else if (type == type::PORTAL)
    {
        cell.setTexture(texture_manager.get_texture("f"));
    }
    else if (type == type::POWER)
    {
        // If the power up has not been eaten yet
        if (toggled)
        {
            // If the power up is a power pellet
            if (specific_type == power_types::POWER_PELLET)
            {
                cell.setTexture(texture_manager.get_texture("pp"));
            }
        }
        // Else if the power up has been eaten
        else
        {
            cell.setTexture(texture_manager.get_texture("f"));
        }
    }
}

// Draw the board
void Draw_Manager::draw_board(std::vector<std::vector<Occupant_List>> *board, int n_rows, int n_cols, bool outline)
{
    int cell_width, cell_height;

    for (int row = 0; row < n_rows; row++)
    {
        for (int col = 0; col < n_cols; col++)
        {
            sf::RectangleShape cell;

            if (outline)
            {
                cell_width = (SCREEN_WIDTH - (n_cols * (BORDER_OUTLINE_THICKNESS * 2))) / n_cols;
                cell_height = (BODY_HEIGHT - (n_rows * (BORDER_OUTLINE_THICKNESS * 2))) / n_rows;
                cell.setSize(sf::Vector2f(cell_width, cell_height));
                cell.setOutlineThickness(BORDER_OUTLINE_THICKNESS);
                cell.setOutlineColor(sf::Color::White);
                cell.setPosition(sf::Vector2f(col * (SCREEN_WIDTH / n_cols) + BORDER_OUTLINE_THICKNESS, row * (BODY_HEIGHT / n_rows) + BORDER_OUTLINE_THICKNESS));
            }
            else
            {
                cell_width = SCREEN_WIDTH / n_cols;
                cell_height = BODY_HEIGHT / n_rows;
                cell.setSize(sf::Vector2f(cell_width, cell_height));
                cell.setPosition(sf::Vector2f(col * cell_width, row * cell_height));
            }

            // If the cell is a wall
            if ((*board)[row][col].find_occupant(type::WALL))
            {
                Wall *wall = static_cast<Wall *>((*board)[row][col].find_occupant(type::WALL));
                set_texture(cell, type::WALL, wall->get_wall_type());
            }
            // If the cell is a coin
            else if ((*board)[row][col].find_occupant(type::COIN))
            {
                Coin *coin = static_cast<Coin *>((*board)[row][col].find_occupant(type::COIN));
                set_texture(cell, type::COIN, 0, coin->get_toggled());
            }
            // If the cell is a portal
            else if ((*board)[row][col].find_occupant(type::PORTAL))
            {
                set_texture(cell, type::PORTAL, 0);
            }
            // Else if the cell is a power up
            else if ((*board)[row][col].find_occupant(type::POWER))
            {
                Power *power = static_cast<Power *>((*board)[row][col].find_occupant(type::POWER));
                set_texture(cell, type::POWER, power->get_type(), power->get_toggled());
            }
            body->draw(cell);
        }
    }
}

// Draw pacman in accordence with a given start and end position using linear interpolation
void Draw_Manager::pacman_animation(Occupant *pacman, int x, int y, int target_x, int target_y, int direction, float tick, int n_rows, int n_cols)
{
    float *current_position;
    current_position = lerp(x, y, target_x, target_y, tick);

    int cell_width = SCREEN_WIDTH / n_cols;
    int cell_height = BODY_HEIGHT / n_rows;
    draw_pacman(pacman, current_position[0], current_position[1], direction, cell_width, cell_height);

    delete[] current_position;
}

// Draw pacman
void Draw_Manager::draw_pacman(Occupant *pacman, float x, float y, int direction, int cell_width, int cell_height)
{
    sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
    cell.setPosition(sf::Vector2f(y * cell_width, x * cell_height));

    int state = static_cast<Pacman *>(pacman)->get_animation_state();
    if (state == pacman_animation_state::OPEN)
    {
        cell.setTexture(texture_manager.get_texture("fopm"));
    }
    else if (state == pacman_animation_state::HALFWAY)
    {
        cell.setTexture(texture_manager.get_texture("hcpm"));
    }
    else
    {
        cell.setTexture(texture_manager.get_texture("cpm"));
    }

    handle_rotation(pacman, cell, direction, cell_width, cell_height);
    body->draw(cell);
}

// Draw the ghost's in accordence with a given start and end position using linear interpolation
void Draw_Manager::ghost_animation(State_Manager *state_manager, Occupant *ghost, std::string name, float tick, int cell_width, int cell_height)
{
    if (ghost)
    {
        float *current_position;
        current_position = lerp(ghost->get_x_position(), ghost->get_y_position(), static_cast<Ghost *>(ghost)->get_best_x_tile(), static_cast<Ghost *>(ghost)->get_best_y_tile(), tick);

        // If the ghost has been eaten, draw ghost eyes
        if (state_manager->get_ghost_state(static_cast<Ghost *>(ghost)->get_type()) == ghost_states::HEADING_BACK)
        {
            draw_ghost_eyes(ghost, current_position[0], current_position[1], cell_width, cell_height);
        }
        // Else if the ghost is frightened, draw scared ghost
        else if (state_manager->get_ghost_mode() == ghost_modes::FRIGHTENED)
        {
            draw_frightened_ghost(ghost, current_position[0], current_position[1], cell_width, cell_height);
        }
        // Else draw regular ghost
        else
        {
            draw_ghost(ghost, current_position[0], current_position[1], name, cell_width, cell_height);
        }

        delete[] current_position;
    }
}

// Draw all moving ghosts
void Draw_Manager::draw_all_ghost_animation(State_Manager *state_manager, Occupant **characters, Speed_Manager *speed_manager, int n_rows, int n_cols)
{
    std::string names[4] = {"blinky", "pinky", "inky", "clyde"};
    for (int character = 0; character < 4; character++)
    {
        if (characters[character])
        {
            int cell_width = SCREEN_WIDTH / n_cols;
            int cell_height = BODY_HEIGHT / n_rows;
            ghost_animation(state_manager, characters[character], names[character], speed_manager->ghost_clocks[character]->get_tick(), cell_width, cell_height);
        }
    }
}

// Draw a given ghost
void Draw_Manager::draw_ghost(Occupant *ghost, float x, float y, std::string name, int cell_width, int cell_height)
{
    if (ghost)
    {
        sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
        cell.setPosition(sf::Vector2f(y * cell_width, x * cell_height));

        if (ghost->get_direction() == moves::UP)
        {
            cell.setTexture(texture_manager.get_texture(name + "u"));
        }
        else if (ghost->get_direction() == moves::RIGHT)
        {
            cell.setTexture(texture_manager.get_texture(name + "r"));
        }
        else if (ghost->get_direction() == moves::DOWN)
        {
            cell.setTexture(texture_manager.get_texture(name + "d"));
        }
        else
        {
            cell.setTexture(texture_manager.get_texture(name + "l"));
        }

        body->draw(cell);
    }
}

// Draw all static ghosts
void Draw_Manager::draw_all_ghosts(Occupant **characters, int n_rows, int n_cols)
{
    std::string names[4] = {"blinky", "pinky", "inky", "clyde"};
    for (int character = 0; character < 4; character++)
    {
        if (characters[character])
        {
            int cell_width = SCREEN_WIDTH / n_cols;
            int cell_height = BODY_HEIGHT / n_rows;
            draw_ghost(characters[character], characters[character]->get_x_position(), characters[character]->get_y_position(), names[character], cell_width, cell_height);
        }
    }
}

// Draw a frightened ghost
void Draw_Manager::draw_frightened_ghost(Occupant *ghost, float x, float y, int cell_width, int cell_height)
{
    sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
    cell.setPosition(sf::Vector2f(y * cell_width, x * cell_height));
    cell.setTexture(texture_manager.get_texture("frightened"));
    body->draw(cell);
}

// Draw ghost eyes
void Draw_Manager::draw_ghost_eyes(Occupant *ghost, float x, float y, int cell_width, int cell_height)
{
    sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
    cell.setPosition(sf::Vector2f(y * cell_width, x * cell_height));

    if (ghost->get_direction() == moves::UP)
    {
        cell.setTexture(texture_manager.get_texture("eyesu"));
    }
    else if (ghost->get_direction() == moves::RIGHT)
    {
        cell.setTexture(texture_manager.get_texture("eyesr"));
    }
    else if (ghost->get_direction() == moves::DOWN)
    {
        cell.setTexture(texture_manager.get_texture("eyesd"));
    }
    else if (ghost->get_direction() == moves::LEFT)
    {
        cell.setTexture(texture_manager.get_texture("eyesl"));
    }

    body->draw(cell);
}
