#include "engine.h"
#include "draw_manager.h"
#include "clock.h"
#include "SFML/Graphics.hpp"
#include "linear_directions.h"

int main()
{
    Engine e("map.txt");

    int screen_width = 700;
    int body_height = 775;
    int header_height = 100;

    sf::RenderWindow window(sf::VideoMode(screen_width, body_height + header_height), "Pac-Man");
    sf::RenderTexture body;
    sf::RenderTexture header;

    body.create(screen_width, body_height);
    header.create(screen_width, header_height);

    Draw_Manager d(window, body, header, screen_width, body_height, header_height, e.get_board()->get_rows(), e.get_board()->get_cols());

    sf::Event event;

    e.get_state_manager()->set_ghost_escape_tile(ghosts_types::BLINKY, 12, 14);
    e.get_state_manager()->set_ghost_escape_tile(ghosts_types::PINKY, 12, 14);
    e.get_state_manager()->set_ghost_escape_tile(ghosts_types::INKY, 12, 14);
    e.get_state_manager()->set_ghost_escape_tile(ghosts_types::CLYDE, 12, 14);

    Clock player_clock(200);
    Clock ghost_clock(300);
    Clock player_animation_clock(100);

    e.get_state_manager()->push(7000, ghost_modes::SCATTER);
    e.get_state_manager()->push(20000, ghost_modes::CHASE);

    bool is_stopped = false;
    int buffer_direction = e.get_pacman()->get_direction();
    int intended_direction = buffer_direction;

    e.get_ai()->move_all(e.get_state_manager());

    while (window.isOpen())
    {
        e.get_points()->stringify();

        // Update all the clocks
        player_clock.update();
        ghost_clock.update();
        player_animation_clock.update();
        e.get_state_manager()->update_mode();

        // If pacman has moved over one coin on on the screen (pacman is drawn ahead before he is moved internally)
        if (player_clock.need_restart())
        {
            player_clock.restart();

            bool *moves = e.get_navigation()->get_possible_moves(e.get_pacman(), e.get_board());

            // If pacman is able to move in the intended direction, and pacman is not trying to reverse in-between cells
            if (moves[intended_direction] && e.get_pacman()->get_direction() == buffer_direction)
            {
                // Move pacman in the intended direction and set his buffer_direction to face the same way
                int powerup = -1;
                e.get_navigation()->move(e.get_pacman(), e.get_board(), intended_direction, e.get_points(), &powerup);
                if (powerup == power_types::POWER_PELLET)
                {
                    e.get_state_manager()->overide_mode(10000, ghost_modes::FRIGHTENED);
                }
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
                int powerup = -1;
                e.get_navigation()->move(e.get_pacman(), e.get_board(), buffer_direction, e.get_points(), &powerup);
                if (powerup == power_types::POWER_PELLET)
                {
                    e.get_state_manager()->overide_mode(10000, ghost_modes::FRIGHTENED);
                }

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
            delete[] moves;
        }

        // Check for collisions
        // Note: Collission must happen between pacman's move call and
        //       the ghosts move call or else if they are in adjacent cells,
        //       pacman might phase through the ghost at a pixel perfect frame
        //       as they swap places
        if (e.check_collision())
        {
            e.get_life_manager()->set_collision(true);
            e.get_life_manager()->decrement();

            if (e.get_state_manager()->get_ghost_mode() != ghost_modes::FRIGHTENED)
            {
                ghost_clock.restart();
                player_clock.restart();
                e.reset_all_positions();
                e.get_state_manager()->set_ghost_state(ghosts_types::BLINKY, ghost_states::ESCAPING);
                e.get_state_manager()->set_ghost_state(ghosts_types::PINKY, ghost_states::ESCAPING);
                e.get_state_manager()->set_ghost_state(ghosts_types::INKY, ghost_states::ESCAPING);
                e.get_state_manager()->set_ghost_state(ghosts_types::CLYDE, ghost_states::ESCAPING);
            }
            else
            {
                (*(e.get_board()->get_board()))[e.get_pacman()->get_x_position()][e.get_pacman()->get_y_position()].set_state_of_all_ghosts(e.get_state_manager(), ghost_states::HEADING_BACK);
            }
        }

        // If the ghosts have moved one coin over (the ghosts are drawn ahead before they are moved internally)
        // Note: The move call must be called before the AI call or else the lerp animation
        //       won't function properly. This is because if we call AI first, the ghost will calculate the target
        //       tile based on his position before he is moved, not the position drawn on the screen. Meaning that
        //       the draw call will draw the ghost to where he already is, rendering the lerp animation useless.
        if (ghost_clock.need_restart())
        {
            e.get_navigation()->move_all_ghosts(e.get_board(), e.get_blinky(), e.get_pinky(), e.get_inky(), e.get_clyde());

            // If the current ghost mode is scatter, call the scatter AI
            e.get_ai()->move_all(e.get_state_manager());

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

        d.clear_all();

        d.draw_board(e.get_board()->get_board());

        // If there is no collision, draw lerping animation
        if (!e.get_life_manager()->get_collision() || e.get_state_manager()->get_ghost_mode() == ghost_modes::FRIGHTENED)
        {
            bool frightened;
            frightened = (e.get_state_manager()->get_ghost_mode() == ghost_modes::FRIGHTENED);
            d.ghost_animation(e.get_blinky(), "blinky", ghost_clock.get_tick(), frightened, e.get_state_manager()->get_ghost_state(ghosts_types::BLINKY));
            d.ghost_animation(e.get_pinky(), "pinky", ghost_clock.get_tick(), frightened, e.get_state_manager()->get_ghost_state(ghosts_types::PINKY));
            d.ghost_animation(e.get_inky(), "inky", ghost_clock.get_tick(), frightened, e.get_state_manager()->get_ghost_state(ghosts_types::INKY));
            d.ghost_animation(e.get_clyde(), "clyde", ghost_clock.get_tick(), frightened, e.get_state_manager()->get_ghost_state(ghosts_types::CLYDE));

            if (e.get_life_manager()->get_collision())
            {
                e.get_life_manager()->set_collision(false);
            }
        }
        // Else if there is a collision, reset positions and decrease lives
        else
        {
            d.draw_ghost(e.get_blinky(), e.get_blinky()->get_x_position(), e.get_blinky()->get_y_position(), "blinky");
            d.draw_ghost(e.get_pinky(), e.get_pinky()->get_x_position(), e.get_pinky()->get_y_position(), "pinky");
            d.draw_ghost(e.get_inky(), e.get_inky()->get_x_position(), e.get_inky()->get_y_position(), "inky");
            d.draw_ghost(e.get_clyde(), e.get_clyde()->get_x_position(), e.get_clyde()->get_y_position(), "clyde");

            e.get_ai()->move_all(e.get_state_manager());

            e.get_life_manager()->set_collision(false);
        }

        int x = e.get_pacman()->get_x_position();
        int y = e.get_pacman()->get_y_position();

        int target_x = x + linear_directions_one[e.get_pacman()->get_direction()][0];
        int target_y = y + linear_directions_one[e.get_pacman()->get_direction()][1];

        // If pacman is stopped
        if ((*(e.get_board()->get_board()))[target_x][target_y].find_occupant(type::WALL))
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

        d.draw_score(e.get_points());
        d.draw_all();
    }

    return 0;
}