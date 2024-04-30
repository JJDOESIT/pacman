#include "engine.h"
#include "draw_manager.h"
#include "clock.h"
#include "speed_manager.h"
#include "SFML/Graphics.hpp"
#include "linear_directions.h"
#include "config.h"

int main()
{
    Engine e(Config::MAP_DIR + "map0.txt");

    sf::RenderWindow window(sf::VideoMode(Config::SCREEN_WIDTH, Config::HEADER_HEIGHT + Config::BODY_HEIGHT + Config::FOOTER_HEIGHT), "Pac-Man");
    sf::RenderTexture body;
    sf::RenderTexture header;
    sf::RenderTexture footer;

    header.create(Config::SCREEN_WIDTH, Config::HEADER_HEIGHT);
    body.create(Config::SCREEN_WIDTH, Config::BODY_HEIGHT);
    footer.create(Config::SCREEN_WIDTH, Config::FOOTER_HEIGHT);

    Draw_Manager d(window, header, body, footer, e.get_board()->get_rows(), e.get_board()->get_cols());

    e.get_map_editor()->create_map(10, 10);

    e.get_map_editor()->initilize_tiles(&d, 20);

    sf::Event event;

    Clock player_animation_clock(100);

    bool is_stopped = false;
    int buffer_direction = e.get_character(characters::PACMAN)->get_direction();
    int intended_direction = buffer_direction;

    e.get_ai()->move_all(e.get_state_manager(), e.get_speed_manager());
    std::cout << e.get_character(2)->get_y_position() << ", " << static_cast<Ghost *>(e.get_character(2))->get_best_y_tile() << std::endl;

    while (window.isOpen())
    {
        if (!e.get_map_editor()->is_editing())
        {
            e.get_points()->stringify();

            // Update all the clocks
            e.get_speed_manager()->update_all();
            player_animation_clock.update();
            e.get_state_manager()->update_mode();
            e.get_state_manager()->update_states();

            // If pacman has moved over one coin on on the screen (pacman is drawn ahead before he is moved internally)
            if (e.get_speed_manager()->pacman_clock->need_restart())
            {
                e.get_speed_manager()->pacman_clock->restart();

                bool *moves = e.get_navigation()->get_possible_moves(e.get_character(characters::PACMAN), e.get_board());

                // Else if pacman is trying to reverse between cells
                // ie. Pacman internally is moving right, but on screen moving left
                if (e.get_character(characters::PACMAN)->get_direction() != buffer_direction)
                {
                    // Set pacman's internal direction to the buffer direction
                    // Note: This is because this means pacman has successfully turned around and reached
                    //       original starting position. When we update his internal position to reflect this,
                    //       his target tile will now be the correct tile.
                    e.get_character(characters::PACMAN)->set_direction(buffer_direction);
                }
                else
                {
                    int direction;

                    // If pacman is able to move in the intended direction, and pacman is not trying to reverse in-between cells
                    if (moves[intended_direction] && e.get_character(characters::PACMAN)->get_direction() == buffer_direction)
                    {
                        direction = intended_direction;
                    }
                    // Else if pacman is moving along a straight path
                    else
                    {
                        direction = buffer_direction;
                    }

                    // Move pacman
                    int powerup = -1;
                    e.get_navigation()->move(e.get_character(characters::PACMAN), e.get_board(), direction, e.get_points(), &powerup);
                    // If a power pellet was eaten
                    if (powerup == power_types::POWER_PELLET)
                    {
                        // Set the ghost mode to frightened
                        e.get_state_manager()->overide_mode(10000, ghost_modes::FRIGHTENED);

                        // If a ghost was not already eaten, set its speed to slow down
                        for (int ghost = 0; ghost < 4; ghost++)
                        {
                            if (e.get_state_manager()->get_ghost_state(ghost) != ghost_states::HEADING_BACK)
                            {
                                if (e.get_state_manager()->get_ghost_mode() != ghost_modes::FRIGHTENED)
                                {
                                    e.get_speed_manager()->set_threshold(ghost, 400);
                                    e.get_state_manager()->get_ghost_state_clock(ghost)->restart();
                                    e.get_state_manager()->get_ghost_state_clock(ghost)->set_threshold(10000);
                                    e.get_state_manager()->get_ghost_state_clock(ghost)->delay_a_function([ghost, &e]()
                                                                                                          { e.get_speed_manager()->update_ghost_speed(ghost, e.get_speed_manager()->get_initial_time(type::GHOST)); });
                                }
                                else
                                {
                                    e.get_state_manager()->get_ghost_state_clock(ghost)->restart(false);
                                }
                            }
                        }
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
                    bool *moves = e.get_navigation()->get_possible_moves(e.get_character(characters::PACMAN), e.get_board());
                    if (moves[intended_direction])
                    {
                        buffer_direction = intended_direction;
                        e.get_character(characters::PACMAN)->set_direction(buffer_direction);
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
                // Set collision to be true
                e.get_life_manager()->set_collision(true);

                // If pacman has collided with a ghost while they are in normal mode
                if (e.get_state_manager()->get_ghost_mode() != ghost_modes::FRIGHTENED)
                {
                    // Decrease lives by one, restart their clocks, reset all positions and states
                    e.get_life_manager()->decrement();
                    e.get_speed_manager()->reset_all();
                    e.get_speed_manager()->pacman_clock->restart();
                    e.get_navigation()->reset_all_characters(e.get_board(), e.get_all_characters());
                    e.get_state_manager()->reset();
                }
                else
                {
                    std::vector<Occupant *> occupants = (*(e.get_board()->get_board()))[e.get_character(characters::PACMAN)->get_x_position()][e.get_character(characters::PACMAN)->get_y_position()].get_all_occupants(type::GHOST);
                    for (Occupant *occupant : occupants)
                    {
                        e.get_state_manager()->set_ghost_state(static_cast<Ghost *>(occupant)->get_type(), ghost_states::HEADING_BACK);
                        e.get_speed_manager()->set_threshold(static_cast<Ghost *>(occupant)->get_type(), 150);
                    }
                }
            }

            // If the ghosts have moved one coin over (the ghosts are drawn ahead before they are moved internally)
            // Note: The move call must be called before the AI call or else the lerp animation
            //       won't function properly. This is because if we call AI first, the ghost will calculate the target
            //       tile based on his position before he is moved, not the position drawn on the screen. Meaning that
            //       the draw call will draw the ghost to where he already is, rendering the lerp animation useless.
            for (int ghost = 0; ghost < 4; ghost++)
            {
                // If the ghosts has moved one coin over
                if (e.get_speed_manager()->ghost_clocks[ghost]->need_restart())
                {
                    // Move the ghosts corresponding to their internal direction
                    if (e.get_character(ghost))
                    {
                        // Calculate the ghosts new direction given their current state
                        e.get_ai()->move_based_on_state(e.get_state_manager(), e.get_speed_manager(), ghost, true);
                        e.get_speed_manager()->ghost_clocks[ghost]->restart();
                    }
                }
            }

            if (player_animation_clock.need_restart())
            {
                Pacman *pacman = static_cast<Pacman *>(e.get_character(characters::PACMAN));
                pacman->set_animation_state((pacman->get_animation_state() + 1) % 3);
                player_animation_clock.restart();
            }
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (!e.get_map_editor()->is_editing())
                {

                    bool *moves = e.get_navigation()->get_possible_moves(e.get_character(characters::PACMAN), e.get_board());

                    if (event.key.code == sf::Keyboard::R)
                    {
                        e.reset();
                        e.initilize(Config::MAP_DIR + "map1.txt");
                        e.get_ai()->move_all(e.get_state_manager(), e.get_speed_manager());
                    }
                    else if (event.key.code == sf::Keyboard::E)
                    {
                        e.get_map_editor()->toggle_editing(true);
                    }
                    else if (event.key.code == sf::Keyboard::W)
                    {
                        if (moves[moves::UP] && buffer_direction != moves::UP)
                        {
                            e.get_speed_manager()->pacman_clock->update(e.get_speed_manager()->pacman_clock->get_threshold() - e.get_speed_manager()->pacman_clock->get_time());
                            buffer_direction = moves::UP;
                            intended_direction = buffer_direction;
                            if (is_stopped)
                            {
                                e.get_speed_manager()->pacman_clock->restart();
                                e.get_character(characters::PACMAN)->set_direction(moves::UP);
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
                            e.get_speed_manager()->pacman_clock->update(e.get_speed_manager()->pacman_clock->get_threshold() - e.get_speed_manager()->pacman_clock->get_time());
                            buffer_direction = moves::RIGHT;
                            intended_direction = buffer_direction;
                            if (is_stopped)
                            {
                                e.get_speed_manager()->pacman_clock->restart();
                                e.get_character(characters::PACMAN)->set_direction(moves::RIGHT);
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
                            e.get_speed_manager()->pacman_clock->update(e.get_speed_manager()->pacman_clock->get_threshold() - e.get_speed_manager()->pacman_clock->get_time());
                            buffer_direction = moves::DOWN;
                            intended_direction = buffer_direction;
                            if (is_stopped)
                            {
                                e.get_speed_manager()->pacman_clock->restart();
                                e.get_character(characters::PACMAN)->set_direction(moves::DOWN);
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
                            e.get_speed_manager()->pacman_clock->update(e.get_speed_manager()->pacman_clock->get_threshold() - e.get_speed_manager()->pacman_clock->get_time());
                            buffer_direction = moves::LEFT;
                            intended_direction = buffer_direction;
                            if (is_stopped)
                            {
                                e.get_speed_manager()->pacman_clock->restart();
                                e.get_character(characters::PACMAN)->set_direction(moves::LEFT);
                            }
                        }
                        else if (buffer_direction != moves::LEFT)
                        {
                            intended_direction = moves::LEFT;
                        }
                    }
                }
                else
                {
                    if (event.key.code == sf::Keyboard::P)
                    {
                        e.get_map_editor()->toggle_editing(false);
                        e.get_speed_manager()->restart_all();
                        player_animation_clock.restart();
                        e.get_state_manager()->reset();
                    }
                    else if (event.key.code == sf::Keyboard::S)
                    {
                        e.get_map_editor()->array_to_file();
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (e.get_map_editor()->is_editing())
                {
                    float x = sf::Mouse::getPosition(window).x;
                    float y = sf::Mouse::getPosition(window).y;

                    y -= (Config::HEADER_HEIGHT + Config::BODY_HEIGHT);
                    for (int i = 0; i < e.get_map_editor()->get_tile_set()->size(); i++)
                    {
                        sf::FloatRect bounding_box = (*(e.get_map_editor()->get_tile_set()))[i].get_rect().getGlobalBounds();

                        if (bounding_box.contains(x, y))
                        {
                            e.get_map_editor()->select_tile(x, y);
                        }
                    }

                    y += Config::BODY_HEIGHT;
                    if (y >= 0 && y <= Config::BODY_HEIGHT)
                    {
                        e.get_map_editor()->add_tile(x, y);
                    }
                }
            }
        }

        d.clear_all();

        if (!(e.get_map_editor()->is_editing()))
        {
            d.draw_board(e.get_board()->get_board(), e.get_board()->get_rows(), e.get_board()->get_cols());

            // If there is no collision or if the ghosts are frightened, draw lerping animation
            if (!e.get_life_manager()->get_collision() || e.get_state_manager()->get_ghost_mode() == ghost_modes::FRIGHTENED)
            {
                d.draw_all_ghost_animation(e.get_state_manager(), e.get_all_characters(), e.get_speed_manager(), e.get_board()->get_rows(), e.get_board()->get_cols());

                // If a collision occured, set the collision to false
                if (e.get_life_manager()->get_collision())
                {
                    e.get_life_manager()->set_collision(false);
                }
            }
            // Else if there is a collision, reset positions and decrease lives
            else
            {
                d.draw_all_ghosts(e.get_all_characters(), e.get_board()->get_rows(), e.get_board()->get_cols());

                e.get_ai()->move_all(e.get_state_manager(), e.get_speed_manager());

                e.get_life_manager()->set_collision(false);
            }

            int x = e.get_character(characters::PACMAN)->get_x_position();
            int y = e.get_character(characters::PACMAN)->get_y_position();

            int target_x = x + linear_directions_one[e.get_character(characters::PACMAN)->get_direction()][0];
            int target_y = y + linear_directions_one[e.get_character(characters::PACMAN)->get_direction()][1];

            // If pacman is stopped
            bool *moves = e.get_navigation()->get_possible_moves(e.get_character(characters::PACMAN), e.get_board());
            if (!moves[e.get_character(characters::PACMAN)->get_direction()])
            {
                d.pacman_animation(e.get_character(characters::PACMAN), x, y, x, y, buffer_direction, e.get_speed_manager()->pacman_clock->get_tick(), e.get_board()->get_rows(), e.get_board()->get_cols());
                is_stopped = true;
            }
            // Else if pacman is moving along a straight path
            else if (buffer_direction == e.get_character(characters::PACMAN)->get_direction())
            {
                d.pacman_animation(e.get_character(characters::PACMAN), x, y, target_x, target_y, buffer_direction, e.get_speed_manager()->pacman_clock->get_tick(), e.get_board()->get_rows(), e.get_board()->get_cols());
                is_stopped = false;
            }
            // Else if pacman is reversing between cells
            else
            {
                d.pacman_animation(e.get_character(characters::PACMAN), target_x, target_y, x, y, buffer_direction, e.get_speed_manager()->pacman_clock->get_tick(), e.get_board()->get_rows(), e.get_board()->get_cols());
                is_stopped = false;
            }

            delete[] moves;

            d.draw_score(e.get_points());
        }
        else
        {
            d.draw_board(e.get_map_editor()->get_board(), e.get_map_editor()->get_n_rows(), e.get_map_editor()->get_n_cols(), true);
            d.draw_tiles(e.get_map_editor()->get_tile_set());
        }

        d.draw_all();
    }

    return 0;
}