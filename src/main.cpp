#include "engine.h"
#include "draw_manager.h"
#include "SFML/Graphics.hpp"

int main()
{
    Engine e("map.txt");

    int s_width = 700;
    int s_height = 775;

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
                    e.get_navigation()->move(e.get_pacman(), e.get_board(), moves::UP);
                    e.get_ai()->pinky(e.get_board(), e.get_navigation(), e.get_pinky(), e.get_pacman());
                    e.get_ai()->clyde(e.get_board(), e.get_navigation(), e.get_clyde(), e.get_pacman());
                    e.get_ai()->blinky(e.get_board(), e.get_navigation(), e.get_blinky(), e.get_pacman());
                    e.get_ai()->inky(e.get_board(), e.get_navigation(), e.get_inky(), e.get_blinky(), e.get_pacman());
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    e.get_navigation()->move(e.get_pacman(), e.get_board(), moves::RIGHT);
                    e.get_ai()->pinky(e.get_board(), e.get_navigation(), e.get_pinky(), e.get_pacman());
                    e.get_ai()->clyde(e.get_board(), e.get_navigation(), e.get_clyde(), e.get_pacman());
                    e.get_ai()->blinky(e.get_board(), e.get_navigation(), e.get_blinky(), e.get_pacman());
                    e.get_ai()->inky(e.get_board(), e.get_navigation(), e.get_inky(), e.get_blinky(), e.get_pacman());
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    e.get_navigation()->move(e.get_pacman(), e.get_board(), moves::DOWN);
                    e.get_ai()->pinky(e.get_board(), e.get_navigation(), e.get_pinky(), e.get_pacman());
                    e.get_ai()->clyde(e.get_board(), e.get_navigation(), e.get_clyde(), e.get_pacman());
                    e.get_ai()->blinky(e.get_board(), e.get_navigation(), e.get_blinky(), e.get_pacman());
                    e.get_ai()->inky(e.get_board(), e.get_navigation(), e.get_inky(), e.get_blinky(), e.get_pacman());
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    e.get_navigation()->move(e.get_pacman(), e.get_board(), moves::LEFT);
                    e.get_ai()->pinky(e.get_board(), e.get_navigation(), e.get_pinky(), e.get_pacman());
                    e.get_ai()->clyde(e.get_board(), e.get_navigation(), e.get_clyde(), e.get_pacman());
                    e.get_ai()->blinky(e.get_board(), e.get_navigation(), e.get_blinky(), e.get_pacman());
                    e.get_ai()->inky(e.get_board(), e.get_navigation(), e.get_inky(), e.get_blinky(), e.get_pacman());
                }
            }
        }

        window.clear();

        std::vector<std::vector<Occupant_List>> *board = e.get_board()->get_board();
        d.draw_board(e.get_board()->get_board());
        d.draw_pacman(e.get_pacman());
        d.draw_ghost(e.get_blinky(), "blinky");
        d.draw_ghost(e.get_pinky(), "pinky");
        d.draw_ghost(e.get_inky(), "inky");
        d.draw_ghost(e.get_clyde(), "clyde");

        window.display();
    }

    return 0;
}