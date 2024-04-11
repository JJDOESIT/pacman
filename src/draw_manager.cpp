#include "draw_manager.h"

Draw_Manager::Draw_Manager(sf::RenderWindow &w, sf::RenderTexture &b, sf::RenderTexture &h, int s_width, int b_height, int h_height, int rows, int cols)
{
    window = &w;
    body = &b;
    header = &h;
    screen_width = s_width;
    body_height = b_height;
    header_height = h_height;
    nRows = rows;
    nCols = cols;
    cell_width = screen_width / cols;
    cell_height = body_height / rows;
}

void Draw_Manager::handle_rotation(Occupant *occupant, sf::RectangleShape &cell, int direction)
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

void Draw_Manager::draw_score(Points *p)
{
    p->stringify();
    text_manager.set_text(p->get_points_string(), TEXT_HEIGHT, sf::Color::White);
    sf::Text text = text_manager.get_text();
    text.setPosition(sf::Vector2f(10, (header_height / 2) - (TEXT_HEIGHT / 2)));
    header->draw(text);
}

// Clear the display
void Draw_Manager::clear_all()
{
    window->clear();
    body->clear();
    header->clear();
}

// Draw the display
void Draw_Manager::draw_all()
{
    body->display();
    header->display();
    sf::Sprite body_texture(body->getTexture());
    sf::Sprite header_texture(header->getTexture());
    body_texture.setPosition(0, header_height);
    window->draw(body_texture);
    window->draw(header_texture);
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

// Draw the board
void Draw_Manager::draw_board(std::vector<std::vector<Occupant_List>> *board)
{
    for (int row = 0; row < nRows; row++)
    {
        for (int col = 0; col < nCols; col++)
        {
            sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
            cell.setPosition(sf::Vector2f(col * cell_width, row * cell_height));

            // If the cell is a wall
            if ((*board)[row][col].find_occupant(type::WALL))
            {
                int wall_type = static_cast<Wall *>((*board)[row][col].find_occupant(type::WALL))->get_wall_type();
                if (wall_type == wall_type::SHARPTOPLEFTCORNER)
                {
                    cell.setTexture(texture_manager.get_texture("stlc"));
                }
                else if (wall_type == wall_type::SHARPTOPRIGHTCORNER)
                {
                    cell.setTexture(texture_manager.get_texture("strc"));
                }
                else if (wall_type == wall_type::SHARPBOTTOMLEFTCORNER)
                {
                    cell.setTexture(texture_manager.get_texture("sblc"));
                }
                else if (wall_type == wall_type::SHARPBOTTOMRIGHTCORNER)
                {
                    cell.setTexture(texture_manager.get_texture("sbrc"));
                }
                else if (wall_type == wall_type::TOPRIGHTCORNERCONNECTOR)
                {
                    cell.setTexture(texture_manager.get_texture("trcc"));
                }
                else if (wall_type == wall_type::TOPLEFTCORNERCONNECTOR)
                {
                    cell.setTexture(texture_manager.get_texture("tlcc"));
                }
                else if (wall_type == wall_type::TOPLEFTCORNERCONNECTORVERTICAL)
                {
                    cell.setTexture(texture_manager.get_texture("tlccv"));
                }
                else if (wall_type == wall_type::TOPRIGHTCORNERCONNECTORVERTICAL)
                {
                    cell.setTexture(texture_manager.get_texture("trccv"));
                }
                else if (wall_type == wall_type::BOTTOMLEFTCORNERCONNECTORVERTICAL)
                {
                    cell.setTexture(texture_manager.get_texture("blccv"));
                }
                else if (wall_type == wall_type::BOTTOMRIGHTCORNERCONNECTORVERTICAL)
                {
                    cell.setTexture(texture_manager.get_texture("brccv"));
                }
                else if (wall_type == wall_type::TOPLEFTCORNERDOUBLE)
                {
                    cell.setTexture(texture_manager.get_texture("tlcd"));
                }
                else if (wall_type == wall_type::TOPRIGHTCORNERDOUBLE)
                {
                    cell.setTexture(texture_manager.get_texture("trcd"));
                }
                else if (wall_type == wall_type::BOTTOMRIGHTCORNERDOUBLE)
                {
                    cell.setTexture(texture_manager.get_texture("brcd"));
                }
                else if (wall_type == wall_type::BOTTOMLEFTCORNERDOUBLE)
                {
                    cell.setTexture(texture_manager.get_texture("blcd"));
                }
                if (wall_type == wall_type::TOPLEFTCORNERSINGLE)
                {
                    cell.setTexture(texture_manager.get_texture("tlcs"));
                }
                else if (wall_type == wall_type::TOPRIGHTCORNERSINGLE)
                {
                    cell.setTexture(texture_manager.get_texture("trcs"));
                }
                else if (wall_type == wall_type::BOTTOMRIGHTCORNERSINGLE)
                {
                    cell.setTexture(texture_manager.get_texture("brcs"));
                }
                else if (wall_type == wall_type::BOTTOMLEFTCORNERSINGLE)
                {
                    cell.setTexture(texture_manager.get_texture("blcs"));
                }
                else if (wall_type == wall_type::TOPLEFTCORNERSINGLECONNECTOR)
                {
                    cell.setTexture(texture_manager.get_texture("tlcsc"));
                }
                else if (wall_type == wall_type::TOPRIGHTCORNERSINGLECONNECTOR)
                {
                    cell.setTexture(texture_manager.get_texture("trcsc"));
                }
                else if (wall_type == wall_type::BOTTOMRIGHTCORNERSINGLECONNECTOR)
                {
                    cell.setTexture(texture_manager.get_texture("brcsc"));
                }
                else if (wall_type == wall_type::BOTTOMLEFTCORNERSINGLECONNECTOR)
                {
                    cell.setTexture(texture_manager.get_texture("blcsc"));
                }
                else if (wall_type == wall_type::STRAIGHTVERTICALLEFTDOUBLE)
                {
                    cell.setTexture(texture_manager.get_texture("svld"));
                }
                else if (wall_type == wall_type::STRAIGHTVERTICALRIGHTDOUBLE)
                {
                    cell.setTexture(texture_manager.get_texture("svrd"));
                }
                else if (wall_type == wall_type::STRAIGHTVERTICALMIDDLELEFT)
                {
                    cell.setTexture(texture_manager.get_texture("svml"));
                }
                else if (wall_type == wall_type::STRAIGHTVERTICALMIDDLERIGHT)
                {
                    cell.setTexture(texture_manager.get_texture("svmr"));
                }
                else if (wall_type == wall_type::STRAIGHTHORIZONTALTOPDOUBLE)
                {
                    cell.setTexture(texture_manager.get_texture("shtd"));
                }
                else if (wall_type == wall_type::STRAIGHTHORIZONTALBOTTOMDOUBLE)
                {
                    cell.setTexture(texture_manager.get_texture("shbd"));
                }
                else if (wall_type == wall_type::STRAIGHTHORIZONTALTOPSINGLE)
                {
                    cell.setTexture(texture_manager.get_texture("shts"));
                }
                else if (wall_type == wall_type::STRAIGHTHORIZONTALBOTTOMSINGLE)
                {
                    cell.setTexture(texture_manager.get_texture("shbs"));
                }
                else if (wall_type == wall_type::FILLED)
                {
                    cell.setTexture(texture_manager.get_texture("f"));
                }
                else if (wall_type == wall_type::GATE)
                {
                    cell.setTexture(texture_manager.get_texture("f"));
                }
            }
            // If the cell is a coin
            else if ((*board)[row][col].find_occupant(type::COIN))
            {
                if (static_cast<Coin *>((*board)[row][col].find_occupant(type::COIN))->get_toggled())
                {
                    cell.setTexture(texture_manager.get_texture("c"));
                }
                else
                {
                    cell.setTexture(texture_manager.get_texture("f"));
                }
            }
            // If the cell is a portal
            else if ((*board)[row][col].find_occupant(type::PORTAL))
            {
                cell.setTexture(texture_manager.get_texture("f"));
            }
            // Else if the cell is a power up
            else if ((*board)[row][col].find_occupant(type::POWER))
            {
                Power *power = static_cast<Power *>((*board)[row][col].find_occupant(type::POWER));

                // If the power up has not been eaten yet
                if (power->get_toggled())
                {
                    // If the power up is a power pellet
                    if (power->get_type() == power_types::POWER_PELLET)
                    {
                        cell.setTexture(texture_manager.get_texture("pp"));
                    }
                }
                else
                {
                    cell.setTexture(texture_manager.get_texture("f"));
                }
            }
            body->draw(cell);
        }
    }
}

// Draw pacman in accordence with a given start and end position using linear interpolation
void Draw_Manager::pacman_animation(Occupant *pacman, int x, int y, int target_x, int target_y, int direction, float tick)
{
    float *current_position;
    current_position = lerp(x, y, target_x, target_y, tick);

    draw_pacman(pacman, current_position[0], current_position[1], direction);

    delete[] current_position;
}

// Draw pacman
void Draw_Manager::draw_pacman(Occupant *pacman, float x, float y, int direction)
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

    handle_rotation(pacman, cell, direction);
    body->draw(cell);
}

// Draw the ghost's in accordence with a given start and end position using linear interpolation
void Draw_Manager::ghost_animation(Occupant *ghost, std::string name, float tick, bool frightened, int state)
{
    if (ghost)
    {
        float *current_position;
        current_position = lerp(ghost->get_x_position(), ghost->get_y_position(), static_cast<Ghost *>(ghost)->get_best_x_tile(), static_cast<Ghost *>(ghost)->get_best_y_tile(), tick);

        if (state == ghost_states::HEADING_BACK)
        {
            draw_ghost_eyes(ghost, current_position[0], current_position[1]);
        }
        else if (frightened)
        {
            draw_frightened_ghost(ghost, current_position[0], current_position[1]);
        }
        else
        {
            draw_ghost(ghost, current_position[0], current_position[1], name);
        }

        delete[] current_position;
    }
}

// Draw a given ghost
void Draw_Manager::draw_ghost(Occupant *ghost, float x, float y, std::string name)
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

// Draw a frightened ghost
void Draw_Manager::draw_frightened_ghost(Occupant *ghost, float x, float y)
{
    sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
    cell.setPosition(sf::Vector2f(y * cell_width, x * cell_height));
    cell.setTexture(texture_manager.get_texture("frightened"));
    body->draw(cell);
}

// Draw ghost eyes
void Draw_Manager::draw_ghost_eyes(Occupant *ghost, float x, float y)
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
