#include "draw_manager.h"

Draw_Manager::Draw_Manager(sf::RenderWindow &w, sf::RenderTexture &h, sf::RenderTexture &b, sf::RenderTexture &f)
{
    window = &w;
    header = &h;
    body = &b;
    footer = &f;
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
    Text_Manager::set_font(p->get_text(), p->get_font(), "fonts/ranchos.otf");
    Text_Manager::set_position(p->get_text(), 10, (Config::HEADER_HEIGHT / 2) - (TEXT_HEIGHT / 2));
    header->draw(*p->get_text());
}

// Draw the tile set for the map editor
void Draw_Manager::draw_tiles(std::vector<Tile> *tiles, int selected_tile)
{
    for (int i = 0; i < tiles->size(); i++)
    {
        if (i == selected_tile)
        {
            (*tiles)[i].get_rect().setOutlineColor(sf::Color::Red);
        }
        else
        {
            (*tiles)[i].get_rect().setOutlineColor(sf::Color::White);
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
    body_texture.setPosition(0, Config::HEADER_HEIGHT);
    footer_texture.setPosition(0, Config::HEADER_HEIGHT + Config::BODY_HEIGHT);
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
    if (type == type::PORTAL)
    {
        cell.setTexture(texture_manager.get_texture("f"));
        return;
    }
    else if (type == type::PLAYER)
    {
        cell.setTexture(texture_manager.get_texture("fopm"));
        return;
    }

    int tile_type, tile_specific_type, tile_toggled;
    rapidjson::Document *document = Json::get_document(Config::JSON_DIR + "tiles.json");
    rapidjson::Value *tile_list = Json::get_object(document, "tiles");

    for (rapidjson::Value::MemberIterator tile = tile_list->MemberBegin(); tile != tile_list->MemberEnd(); tile++)
    {
        tile_type = Json::get_int_from_object(&(tile->value), "type");
        if (tile_type == type::WALL)
        {
            tile_specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
            if (tile_specific_type == specific_type && tile_type == type)
            {
                cell.setTexture(texture_manager.get_texture(std::string(tile->name.GetString())));
                break;
            }
        }
        else if (tile_type == type::COIN)
        {
            if (tile_type == type)
            {
                if (toggled)
                {
                    cell.setTexture(texture_manager.get_texture(std::string(tile->name.GetString())));
                }
                else
                {
                    cell.setTexture(texture_manager.get_texture("f"));
                }
                break;
            }
        }
        else if (tile_type == type::GHOST)
        {
            tile_specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
            if (tile_specific_type == specific_type && tile_type == type)
            {
                cell.setTexture(texture_manager.get_texture(std::string(tile->name.GetString()) + "r"));
                break;
            }
        }
        else if (tile_type == type::POWER)
        {
            tile_specific_type = Json::get_int_from_object(&(tile->value), "specific_type");
            if (tile_specific_type == specific_type && tile_type == type)
            {
                if (toggled)
                {
                    cell.setTexture(texture_manager.get_texture(std::string(tile->name.GetString())));
                }
                else
                {
                    cell.setTexture(texture_manager.get_texture("f"));
                }
                break;
            }
        }
    }
    delete document;
}

// Draw all the buttons in a given button list
void Draw_Manager::draw_buttons(std::vector<Button *> *buttons, int texture_surface)
{
    for (int b = 0; b < (*buttons).size(); b++)
    {
        if (texture_surface == texture_surfaces::HEADER)
        {
            header->draw(*(*buttons)[b]->get_cell());
            header->draw(*(*buttons)[b]->get_text());
        }
        else if (texture_surface == texture_surfaces::BODY)
        {
            body->draw(*(*buttons)[b]->get_cell());
            body->draw(*(*buttons)[b]->get_text());
        }
        else if (texture_surface == texture_surfaces::FOOTER)
        {
            footer->draw(*(*buttons)[b]->get_cell());
            footer->draw(*(*buttons)[b]->get_text());
        }
    }
}

// Draw all the inputs in a given input list
void Draw_Manager::draw_inputs(std::vector<Input *> *inputs, int selected_input, int texture_surface)
{
    for (int b = 0; b < (*inputs).size(); b++)
    {
        sf::Uint8 red = (*(*inputs)[b]->get_cell()).getFillColor().r;
        sf::Uint8 green = (*(*inputs)[b]->get_cell()).getFillColor().g;
        sf::Uint8 blue = (*(*inputs)[b]->get_cell()).getFillColor().b;
        if (b == selected_input)
        {
            (*(*inputs)[b]->get_cell()).setFillColor(sf::Color(red, green, blue, 200));
        }
        else
        {
            (*(*inputs)[b]->get_cell()).setFillColor(sf::Color(red, green, blue));
        }
        if (texture_surface == texture_surfaces::HEADER)
        {
            header->draw(*(*inputs)[b]->get_cell());
            header->draw(*(*inputs)[b]->get_text());
            header->draw(*(*inputs)[b]->get_label_text());
        }
        else if (texture_surface == texture_surfaces::BODY)
        {
            body->draw(*(*inputs)[b]->get_cell());
            body->draw(*(*inputs)[b]->get_text());
            body->draw(*(*inputs)[b]->get_label_text());
        }
        else if (texture_surface == texture_surfaces::FOOTER)
        {
            footer->draw(*(*inputs)[b]->get_cell());
            footer->draw(*(*inputs)[b]->get_text());
            footer->draw(*(*inputs)[b]->get_label_text());
        }
    }
}

// Draw a given number of pacman lives
void Draw_Manager::draw_lives(int n_pacman_lives)
{
    if (n_pacman_lives > 0)
    {
        int cell_size = std::min(int((Config::SCREEN_WIDTH / 2) / n_pacman_lives), int(Config::FOOTER_HEIGHT * 0.5));

        for (int l = 0; l < n_pacman_lives; l++)
        {
            sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
            set_texture(cell, type::PLAYER, 0);
            cell.setPosition(sf::Vector2f(cell_size * l, (Config::FOOTER_HEIGHT / 2) - (cell_size / 2)));
            footer->draw(cell);
        }
    }
}

// Given a board, initilize the textures
void Draw_Manager::initilize_textures(Board *b)
{
    std::vector<std::vector<Occupant_List>> *board = b->get_board();
    int n_rows = b->get_rows();
    int n_cols = b->get_cols();

    for (int row = 0; row < n_rows; row++)
    {
        for (int col = 0; col < n_cols; col++)
        {
            for (auto occupant : (*board)[row][col].get_oc_list())
            {
                if (occupant->get_type() == type::WALL)
                {
                    set_texture(*occupant->get_cell(), occupant->get_type(), static_cast<Wall *>(occupant)->get_wall_type());
                }
                else if (occupant->get_type() == type::COIN)
                {
                    set_texture(*occupant->get_cell(), occupant->get_type(), 0, static_cast<Coin *>(occupant)->get_toggled());
                }
                else if (occupant->get_type() == type::POWER)
                {
                    set_texture(*occupant->get_cell(), occupant->get_type(), static_cast<Power *>(occupant)->get_type(), static_cast<Power *>(occupant)->get_toggled());
                }
                else if (occupant->get_type() == type::PORTAL)
                {
                    set_texture(*occupant->get_cell(), occupant->get_type(), 0);
                }
                else if (occupant->get_type() == type::PLAYER)
                {
                    set_texture(*occupant->get_cell(), occupant->get_type(), 0);
                }
                else if (occupant->get_type() == type::GHOST)
                {
                    set_texture(*occupant->get_cell(), occupant->get_type(), static_cast<Ghost *>(occupant)->get_type());
                }
            }
        }
    }
}

// Draw the board
void Draw_Manager::draw_board(Board *b, bool outline)
{
    std::vector<std::vector<Occupant_List>> board = (*b->get_board());
    int n_rows = b->get_rows();
    int n_cols = b->get_cols();

    int cell_width, cell_height;

    for (int row = 0; row < n_rows; row++)
    {
        for (int col = 0; col < n_cols; col++)
        {
            sf::RectangleShape *cell;
            // If the cell is a wall
            if (board[row][col].find_occupant(type::WALL))
            {
                cell = board[row][col].find_occupant(type::WALL)->get_cell();
            }
            // If the cell is a coin
            else if (board[row][col].find_occupant(type::COIN))
            {
                cell = board[row][col].find_occupant(type::COIN)->get_cell();
            }
            // If the cell is a portal
            else if (board[row][col].find_occupant(type::PORTAL))
            {
                cell = board[row][col].find_occupant(type::PORTAL)->get_cell();
            }
            // Else if the cell is a power up
            else if (board[row][col].find_occupant(type::POWER))
            {
                cell = board[row][col].find_occupant(type::POWER)->get_cell();
            }

            // Note: Ghost and pacman should only be drawn while editing. This is
            //       because during gameplay, the ghosts and pacman are drawn seperate.

            // Else if the cell is a ghost
            else if (board[row][col].find_occupant(type::GHOST))
            {
                cell = board[row][col].find_occupant(type::GHOST)->get_cell();
            }
            // Else if the cell is pacman
            else if (board[row][col].find_occupant(type::PLAYER))
            {
                cell = board[row][col].find_occupant(type::PLAYER)->get_cell();
            }

            if (outline)
            {
                cell_width = (Config::SCREEN_WIDTH - (n_cols * (Config::BORDER_OUTLINE_THICKNESS * 2)) - (n_cols - 1)) / n_cols;
                cell_height = (Config::BODY_HEIGHT - (n_rows * (Config::BORDER_OUTLINE_THICKNESS * 2)) - (n_rows - 1)) / n_rows;
                cell->setSize(sf::Vector2f(cell_width, cell_height));
                cell->setOutlineThickness(Config::BORDER_OUTLINE_THICKNESS);
                cell->setOutlineColor(sf::Color::White);
                cell->setPosition(sf::Vector2f(col * (Config::SCREEN_WIDTH / n_cols) + Config::BORDER_OUTLINE_THICKNESS, row * (Config::BODY_HEIGHT / n_rows) + Config::BORDER_OUTLINE_THICKNESS));
            }
            else
            {
                cell_width = Config::SCREEN_WIDTH / n_cols;
                cell_height = Config::BODY_HEIGHT / n_rows;
                cell->setSize(sf::Vector2f(cell_width, cell_height));
                cell->setPosition(sf::Vector2f(col * cell_width, row * cell_height));
            }

            body->draw(*cell);
        }
    }
}

// Draw pacman in accordence with a given start and end position using linear interpolation
void Draw_Manager::pacman_animation(Occupant *pacman, int x, int y, int target_x, int target_y, int direction, float tick, int n_rows, int n_cols)
{
    float *current_position;
    current_position = lerp(x, y, target_x, target_y, tick);

    int cell_width = Config::SCREEN_WIDTH / n_cols;
    int cell_height = Config::BODY_HEIGHT / n_rows;
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
            int cell_width = Config::SCREEN_WIDTH / n_cols;
            int cell_height = Config::BODY_HEIGHT / n_rows;
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
            int cell_width = Config::SCREEN_WIDTH / n_cols;
            int cell_height = Config::BODY_HEIGHT / n_rows;
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
