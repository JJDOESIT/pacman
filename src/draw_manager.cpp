#include "draw_manager.h"

Draw_Manager::Draw_Manager(sf::RenderWindow &w, int s_width, int s_height, int rows, int cols)
{
    window = &w;
    screen_width = s_width;
    screen_height = s_height;
    nRows = rows;
    nCols = cols;
    cell_width = screen_width / cols;
    cell_height = screen_height / rows;
}

void Draw_Manager::handle_rotation(Occupant *occupant, sf::RectangleShape &cell)
{
    int direction;
    if (occupant->get_type() == type::PLAYER)
    {
        direction = occupant->get_direction();
    }
    else if (occupant->get_type() == type::GHOST)
    {
    }
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
            window->draw(cell);
        }
    }
}

// Draw pacman
void Draw_Manager::draw_pacman(Occupant *pacman)
{
    sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
    cell.setPosition(sf::Vector2f(pacman->get_y_position() * cell_width, pacman->get_x_position() * cell_height));
    cell.setTexture(texture_manager.get_texture("fopm"));
    handle_rotation(pacman, cell);
    window->draw(cell);
}

// Draw a given ghost
void Draw_Manager::draw_ghost(Occupant *ghost, std::string name)
{
    sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
    cell.setPosition(sf::Vector2f(ghost->get_y_position() * cell_width, ghost->get_x_position() * cell_height));

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

    window->draw(cell);
}