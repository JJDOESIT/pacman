#include "engine.h"
#include "draw_manager.h"
#include "SFML/Graphics.hpp"

int main()
{
    Engine e("map.txt");

    int s_width = 700;
    int s_height = 200;

    sf::RenderWindow window(sf::VideoMode(s_width, s_height), "SFML works!");

    Draw_Manager d(window, s_width, s_height, e.get_board()->get_rows(), e.get_board()->get_cols());

    e.get_board()->print_board();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W)
                {
                    bool *moves = e.get_navigation()->get_possible_moves(e.get_pacman(), e.get_board());
                    if (moves[moves::UP])
                    {
                        e.get_navigation()->move_occupant(e.get_pacman(), e.get_board(), moves::UP);
                    }
                    delete moves;
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    bool *moves = e.get_navigation()->get_possible_moves(e.get_pacman(), e.get_board());
                    if (moves[moves::RIGHT])
                    {
                        e.get_navigation()->move_occupant(e.get_pacman(), e.get_board(), moves::RIGHT);
                    }
                    delete moves;
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    bool *moves = e.get_navigation()->get_possible_moves(e.get_pacman(), e.get_board());
                    if (moves[moves::DOWN])
                    {
                        e.get_navigation()->move_occupant(e.get_pacman(), e.get_board(), moves::DOWN);
                    }
                    delete moves;
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    bool *moves = e.get_navigation()->get_possible_moves(e.get_pacman(), e.get_board());
                    if (moves[moves::LEFT])
                    {
                        e.get_navigation()->move_occupant(e.get_pacman(), e.get_board(), moves::LEFT);
                    }
                    delete moves;
                }
            }
        }

        window.clear();

        std::vector<std::vector<Occupant_List>> *board = e.get_board()->get_board();
        d.draw_board(e.get_board()->get_board());
        d.draw_pacman(e.get_pacman());

        window.display();
    }

    return 0;
}