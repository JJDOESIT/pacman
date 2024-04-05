#include "engine.h"
#include "draw_manager.h"
#include "clock.h"
#include "SFML/Graphics.hpp"

int main()
{
    Engine e("map.txt");

    int s_width = 700;
    int s_height = 775;

    sf::RenderWindow window(sf::VideoMode(s_width, s_height), "Pac-Man");

    Draw_Manager d(window, s_width, s_height, e.get_board()->get_rows(), e.get_board()->get_cols());

    sf::Event event;

    Clock player_clock(200);
    Clock ghost_clock(300);
    Clock player_animation_clock(100);

    bool is_stopped = false;
    int buffer_direction = e.get_pacman()->get_direction();
    int intended_direction = buffer_direction;

    e.get_ai()->blinky(e.get_board(), e.get_navigation(), e.get_blinky(), e.get_pacman());
    e.get_ai()->pinky(e.get_board(), e.get_navigation(), e.get_pinky(), e.get_pacman());
    e.get_ai()->inky(e.get_board(), e.get_navigation(), e.get_inky(), e.get_blinky(), e.get_pacman());
    e.get_ai()->clyde(e.get_board(), e.get_navigation(), e.get_clyde(), e.get_pacman());

    while (window.isOpen())
    {
        if (e.check_collision())
        {
            std::cout << "DEAD" << std::endl;
        }
        player_clock.update();
        ghost_clock.update();
        player_animation_clock.update();

        // If pacman has moved over one coin on on the screen (pacman is drawn ahead before he is moved internally)
        if (player_clock.need_restart())
        {
            player_clock.restart();

            bool *moves = e.get_navigation()->get_possible_moves(e.get_pacman(), e.get_board());

            // If pacman is able to move in the intended direction, and pacman is not trying to reverse in-between cells
            if (moves[intended_direction] && e.get_pacman()->get_direction() == buffer_direction)
            {
                // Move pacman in the intended direction and set his buffer_direction to face the same way
                e.get_navigation()->move(e.get_pacman(), e.get_board(), intended_direction);
                buffer_direction = intended_direction;
            }
            // Else if pacman is trying to reverse between cells
            // ie. Pacman internally is moving right, but on screen moving left
            else if (e.get_pacman()->get_direction() != buffer_direction)
            {
                // Set pacman's internal direction to the buffer direction
                // Note: This is because this means pacman has successfully turned around and reached
                //       original starting position. When we update his internal position to reflect this,
                //       his target tile will now be the correct tile.
                e.get_pacman()->set_direction(buffer_direction);
            }
            // Else if pacman is moving along a straight path
            else
            {
                // Move pacman over a tile
                e.get_navigation()->move(e.get_pacman(), e.get_board(), buffer_direction);

                // Recheck if pacman is able to move his intended direction
                // Note: This is needed because if pacman moves up a tile, but is now able to turn his intended
                //       direction the next go-around, his target tile will need to reflect this. If we leave it be,
                //       his target tile be be in the direction he's currently facing, so first he will go towards
                //       that tile. But when the move section sees that he can move to his intended tile, it will
                //       update his position internally, so on the next draw call, he will be drawn from his
                //       target tile to his new position, causing a jump in frames. To solve this, we set
                //       his internal direction to be his intended direction (since he is able to move there),
                //       that way his target tile will be the correct direction.
                bool *moves = e.get_navigation()->get_possible_moves(e.get_pacman(), e.get_board());
                if (moves[intended_direction])
                {
                    buffer_direction = intended_direction;
                    e.get_pacman()->set_direction(buffer_direction);
                }
                delete[] moves;
            }
        }

        if (ghost_clock.need_restart())
        {
            e.get_navigation()->move(e.get_blinky(), e.get_board(), e.get_blinky()->get_direction());
            e.get_ai()->blinky(e.get_board(), e.get_navigation(), e.get_blinky(), e.get_pacman());
            e.get_navigation()->move(e.get_pinky(), e.get_board(), e.get_pinky()->get_direction());
            e.get_ai()->pinky(e.get_board(), e.get_navigation(), e.get_pinky(), e.get_pacman());
            e.get_navigation()->move(e.get_inky(), e.get_board(), e.get_inky()->get_direction());
            e.get_ai()->inky(e.get_board(), e.get_navigation(), e.get_inky(), e.get_blinky(), e.get_pacman());
            e.get_navigation()->move(e.get_clyde(), e.get_board(), e.get_clyde()->get_direction());
            e.get_ai()->clyde(e.get_board(), e.get_navigation(), e.get_clyde(), e.get_pacman());
            ghost_clock.restart();
        }

        if (player_animation_clock.need_restart())
        {
            Pacman *pacman = static_cast<Pacman *>(e.get_pacman());
            pacman->set_animation_state((pacman->get_animation_state() + 1) % 3);
            player_animation_clock.restart();
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                bool *moves = e.get_navigation()->get_possible_moves(e.get_pacman(), e.get_board());

                if (event.key.code == sf::Keyboard::W)
                {
                    if (moves[moves::UP] && buffer_direction != moves::UP)
                    {
                        player_clock.update(player_clock.get_threshold() - player_clock.get_time());
                        buffer_direction = moves::UP;
                        intended_direction = buffer_direction;
                        if (is_stopped)
                        {
                            player_clock.restart();
                            e.get_pacman()->set_direction(moves::UP);
                        }
                    }
                    else if (buffer_direction != moves::UP)
                    {
                        intended_direction = moves::UP;
                    }
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    if (moves[moves::RIGHT] && buffer_direction != moves::RIGHT)
                    {
                        player_clock.update(player_clock.get_threshold() - player_clock.get_time());
                        buffer_direction = moves::RIGHT;
                        intended_direction = buffer_direction;
                        if (is_stopped)
                        {
                            player_clock.restart();
                            e.get_pacman()->set_direction(moves::RIGHT);
                        }
                    }
                    else if (buffer_direction != moves::RIGHT)
                    {
                        intended_direction = moves::RIGHT;
                    }
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    if (moves[moves::DOWN] && buffer_direction != moves::DOWN)
                    {
                        player_clock.update(player_clock.get_threshold() - player_clock.get_time());
                        buffer_direction = moves::DOWN;
                        intended_direction = buffer_direction;
                        if (is_stopped)
                        {
                            player_clock.restart();
                            e.get_pacman()->set_direction(moves::DOWN);
                        }
                    }
                    else if (buffer_direction != moves::DOWN)
                    {

                        intended_direction = moves::DOWN;
                    }
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    if (moves[moves::LEFT] && buffer_direction != moves::LEFT)
                    {
                        player_clock.update(player_clock.get_threshold() - player_clock.get_time());
                        buffer_direction = moves::LEFT;
                        intended_direction = buffer_direction;
                        if (is_stopped)
                        {
                            player_clock.restart();
                            e.get_pacman()->set_direction(moves::LEFT);
                        }
                    }
                    else if (buffer_direction != moves::LEFT)
                    {
                        intended_direction = moves::LEFT;
                    }
                }
            }
        }

        window.clear();

        std::vector<std::vector<Occupant_List>> *board = e.get_board()->get_board();
        d.draw_board(e.get_board()->get_board());

        bool *moves = e.get_navigation()->get_possible_moves(e.get_pacman(), e.get_board());

        int linear_directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        int x = e.get_pacman()->get_x_position();
        int y = e.get_pacman()->get_y_position();

        int target_x = x + linear_directions[e.get_pacman()->get_direction()][0];
        int target_y = y + linear_directions[e.get_pacman()->get_direction()][1];

        // If pacman is stopped
        if (!moves[buffer_direction])
        {
            d.pacman_animation(e.get_pacman(), x, y, x, y, buffer_direction, player_clock.get_tick());
            is_stopped = true;
        }
        // Else if pacman is moving along a straight path
        else if (buffer_direction == e.get_pacman()->get_direction())
        {
            d.pacman_animation(e.get_pacman(), x, y, target_x, target_y, buffer_direction, player_clock.get_tick());
            is_stopped = false;
        }
        // Else if pacman is reversing between cells
        else
        {
            d.pacman_animation(e.get_pacman(), target_x, target_y, x, y, buffer_direction, player_clock.get_tick());
            is_stopped = false;
        }
        delete[] moves;

        d.ghost_animation(e.get_blinky(), "blinky", ghost_clock.get_tick());
        d.ghost_animation(e.get_pinky(), "pinky", ghost_clock.get_tick());
        d.ghost_animation(e.get_inky(), "inky", ghost_clock.get_tick());
        d.ghost_animation(e.get_clyde(), "clyde", ghost_clock.get_tick());

        window.display();
    }

    return 0;
}