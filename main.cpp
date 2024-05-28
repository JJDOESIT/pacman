#include "engine.h"
#include "draw_manager.h"
#include "clock.h"
#include "speed_manager.h"
#include "SFML/Graphics.hpp"
#include "linear_directions.h"
#include "buttons.h"
#include "inputs.h"
#include "config.h"
#include "alert.h"

int main()
{
    Engine e;

    e.initilize();

    int game_state = game_states::NO_MAP;

    sf::RenderWindow window(sf::VideoMode(Config::SCREEN_WIDTH, Config::HEADER_HEIGHT + Config::BODY_HEIGHT + Config::FOOTER_HEIGHT), "Pac-Man");
    sf::RenderTexture body;
    sf::RenderTexture header;
    sf::RenderTexture footer;

    header.create(Config::SCREEN_WIDTH, Config::HEADER_HEIGHT);
    body.create(Config::SCREEN_WIDTH, Config::BODY_HEIGHT);
    footer.create(Config::SCREEN_WIDTH, Config::FOOTER_HEIGHT);

    Draw_Manager d(window, header, body, footer);

    e.get_map_editor()->create_map(10, 10);

    e.get_map_editor()->initilize_tiles(&d, 20);

    d.initilize_textures(e.get_map_editor()->get_board());

    sf::Event event;

    Clock player_animation_clock(100);

    bool is_stopped = false;
    int buffer_direction, intended_direction;

    Buttons editing_header_button_list;
    Buttons playing_header_button_list;
    Buttons loading_map_header_button_list;
    Buttons loading_map_body_button_list;
    Buttons loading_config_body_button_list;
    Buttons selecting_size_header_button_list;
    Buttons selecting_config_name_footer_button_list;
    Buttons playing_footer_button_list;
    Buttons loading_config_footer_button_list;

    Inputs selecting_size_body_input_list;
    Inputs selecting_config_name_body_input_list;

    const int BUTTON_WIDTH = Config::SCREEN_WIDTH / 6;
    const int BUTTON_HEIGHT = Config::HEADER_HEIGHT / 2;
    int MAP_BUTTON_WIDTH = Config::SCREEN_WIDTH / 3;
    int MAP_BUTTON_HEIGHT = Config::BODY_HEIGHT / 6;

    const int INPUT_WIDTH = Config::SCREEN_WIDTH / 4;
    const int INPUT_HEIGHT = Config::HEADER_HEIGHT / 2;

    int BUTTON_CHAR_SIZE = 17;

    editing_header_button_list.push(new Button(Config::SCREEN_WIDTH - BUTTON_WIDTH - (BUTTON_WIDTH / 2), Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE, sf::Color(248, 215, 218), sf::Color(114, 28, 36), "Exit"));
    editing_header_button_list.push(new Button(Config::SCREEN_WIDTH - (2 * BUTTON_WIDTH) - (BUTTON_WIDTH / 2) - 10, Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE, sf::Color(217, 237, 218), sf::Color(21, 87, 36), "Save"));
    playing_header_button_list.push(new Button(Config::SCREEN_WIDTH - BUTTON_WIDTH - (BUTTON_WIDTH / 2), Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE, sf::Color(230, 230, 230), sf::Color::Black, "Create Map"));
    playing_header_button_list.push(new Button(Config::SCREEN_WIDTH - (2 * BUTTON_WIDTH) - (BUTTON_WIDTH / 2) - 10, Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE, sf::Color(230, 230, 230), sf::Color::Black, "Load Map"));
    loading_map_header_button_list.push(new Button(Config::SCREEN_WIDTH - (2 * BUTTON_WIDTH) - (BUTTON_WIDTH / 2) - 10, Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE, sf::Color(248, 215, 218), sf::Color(114, 28, 36), "Exit"));
    selecting_size_header_button_list.push(new Button(Config::SCREEN_WIDTH - BUTTON_WIDTH - (BUTTON_WIDTH / 2), Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE, sf::Color(248, 215, 218), sf::Color(114, 28, 36), "Exit"));
    selecting_size_header_button_list.push(new Button(Config::SCREEN_WIDTH - (2 * BUTTON_WIDTH) - (BUTTON_WIDTH / 2) - 10, Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE, sf::Color(217, 237, 218), sf::Color(21, 87, 36), "Create"));
    selecting_config_name_footer_button_list.push(new Button(Config::SCREEN_WIDTH - BUTTON_WIDTH - (BUTTON_WIDTH / 2), Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE, sf::Color(248, 215, 218), sf::Color(114, 28, 36), "Exit"));
    selecting_config_name_footer_button_list.push(new Button(Config::SCREEN_WIDTH - (2 * BUTTON_WIDTH) - (BUTTON_WIDTH / 2) - 10, Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE, sf::Color(217, 237, 218), sf::Color(21, 87, 36), "Create"));
    playing_footer_button_list.push(new Button(Config::SCREEN_WIDTH - BUTTON_WIDTH - (BUTTON_WIDTH / 2), Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE - 2, sf::Color(230, 230, 230), sf::Color::Black, "Create Config"));
    playing_footer_button_list.push(new Button(Config::SCREEN_WIDTH - (2 * BUTTON_WIDTH) - (BUTTON_WIDTH / 2) - 10, Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE - 2, sf::Color(230, 230, 230), sf::Color::Black, "Load Config"));
    loading_config_footer_button_list.push(new Button(Config::SCREEN_WIDTH - (2 * BUTTON_WIDTH) - (BUTTON_WIDTH / 2) - 10, Config::HEADER_HEIGHT - BUTTON_HEIGHT - (BUTTON_HEIGHT / 2), BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_CHAR_SIZE, sf::Color(248, 215, 218), sf::Color(114, 28, 36), "Exit"));

    selecting_size_body_input_list.push(new Input((Config::SCREEN_WIDTH / 2) - (INPUT_WIDTH / 2), 0, INPUT_WIDTH, INPUT_HEIGHT, 30, sf::Color::White, sf::Color::Black, sf::Color::White, "Rows: "));
    selecting_size_body_input_list.push(new Input((Config::SCREEN_WIDTH / 2) - (INPUT_WIDTH / 2), INPUT_HEIGHT + 10, INPUT_WIDTH, INPUT_HEIGHT, 30, sf::Color::White, sf::Color::Black, sf::Color::White, "Columns: "));
    selecting_config_name_body_input_list.push(new Input((Config::SCREEN_WIDTH / 2) - (INPUT_WIDTH), 0, 2 * INPUT_WIDTH, INPUT_HEIGHT, 30, sf::Color::White, sf::Color::Black, sf::Color::White, "Name: "));

    // Assign the exit function
    (*editing_header_button_list.get_buttons())[0]->set_function([&e, &game_state]()
                                                                 { 
                                                                    e.reset();
                                                                    game_state = game_states::NO_MAP; });

    // Assign the save function
    (*editing_header_button_list.get_buttons())[1]->set_function([&e, &game_state]()
                                                                 { 
                                                                    e.get_map_editor()->array_to_file();
                                                                    game_state = game_states::NO_MAP; });

    // Assign the exit function
    (*loading_map_header_button_list.get_buttons())[0]->set_function([&e, &game_state]()
                                                                     {
                                                                    e.reset();
                                                                    game_state = game_states::NO_MAP; });

    // Assign the exit function
    (*loading_config_footer_button_list.get_buttons())[0]->set_function([&e, &game_state]()
                                                                        { 
                                                                    e.reset();
                                                                    game_state = game_states::NO_MAP; });

    // Assign the exit function
    (*selecting_size_header_button_list.get_buttons())[0]->set_function([&e, &game_state]()
                                                                        {
                                                                    e.reset();
                                                                    game_state = game_states::NO_MAP; });

    // Assign the create function map
    (*selecting_size_header_button_list.get_buttons())[1]->set_function([&e, &game_state, &selecting_size_body_input_list, &d]()
                                                                        { 
                                                                        std::string string_rows = (*selecting_size_body_input_list.get_inputs())[0]->get_text()->getString();
                                                                        std::string string_cols = (*selecting_size_body_input_list.get_inputs())[1]->get_text()->getString();
                                                                        if (string_rows.length() > 0 && string_cols.length() > 0){
                                                                            if (std::stoi(string_rows) > 0 && std::stoi(string_cols) > 0)
                                                                            {
                                                                                if (Json::get_int(Config::JSON_DIR + "map_count.json", "count") >=5){
                                                                                    e.get_alert()->set_text("Limit of 5 Maps");
                                                                                    e.get_alert()->set_toggled(true);
                                                                                }
                                                                                else{
                                                                                    e.get_map_editor()->create_map(std::stoi(string_rows), std::stoi(string_cols));
                                                                                    d.initilize_textures(e.get_map_editor()->get_board());
                                                                                    game_state = game_states::EDITING; 
                                                                                }
                                                                             
                                                                            }   
                                                                        } });

    // Assign the create config function
    (*playing_footer_button_list.get_buttons())[0]->set_function([&game_state, &selecting_config_name_body_input_list]()
                                                                 { 
                                                                    selecting_config_name_body_input_list.set_selected(-1);
                                                                    selecting_config_name_body_input_list.reset();
                                                                    game_state = game_states::SELECTING_CONFIG_NAME; });

    // Assign the exit function
    (*selecting_config_name_footer_button_list.get_buttons())[0]->set_function([&e, &game_state]()
                                                                               { 
                                                                    e.reset();
                                                                    game_state = game_states::NO_MAP; });

    // Assign the create function config
    (*selecting_config_name_footer_button_list.get_buttons())[1]->set_function([&e, &game_state, &selecting_config_name_body_input_list, &d]()
                                                                               { 
                                                                        std::string name = (*selecting_config_name_body_input_list.get_inputs())[0]->get_text()->getString();
                                                                        if (name.length()){      
                                                                            if (Json::get_int(Config::JSON_DIR + "default_config.json", "count") >= 5){
                                                                                e.get_alert()->set_text("Limit of 5 Configs");
                                                                                e.get_alert()->set_toggled(true);
                                                                            }
                                                                            else{
                                                                                e.get_map_editor()->create_config_file(name);
                                                                                Json::set_int(Config::JSON_DIR + "default_config.json", "count", Json::get_int(Config::JSON_DIR + "default_config.json", "count") + 1);
                                                                                game_state = game_states::NO_MAP; 
                                                                            }  
                                                                        } });

    // Assign the create map function
    (*playing_header_button_list.get_buttons())[0]->set_function([&game_state, &e, &selecting_size_body_input_list]()
                                                                 { 
                                                                    e.get_map_editor()->clear_board();
                                                                    selecting_size_body_input_list.set_selected(-1);
                                                                    selecting_size_body_input_list.reset();
                                                                    game_state = game_states::SELECTING_SIZE; });

    (*playing_header_button_list.get_buttons())[1]->set_function([&game_state, &e, &loading_map_body_button_list, &d, &buffer_direction, &intended_direction, &MAP_BUTTON_WIDTH, &BUTTON_HEIGHT, &BUTTON_WIDTH, &MAP_BUTTON_HEIGHT]()
                                                                 { 
                                                                    game_state = game_states::LOADING_MAP;
                                                                    std::vector<std::string> *maps = e.get_map_editor()->map_files();
                                                                    loading_map_body_button_list.clear();
                                                                    for (int m = 0; m < (*maps).size() * 3; m+=3){      
                                                                        sf::Color background_color; 
                                                                        (m / 3) % 2 == 0 ? background_color = sf::Color(224, 224, 224) : background_color = sf::Color(160, 160, 160);
                                                            
                                                                        loading_map_body_button_list.push(new Button(((Config::SCREEN_WIDTH / 2) - (MAP_BUTTON_WIDTH / 2)) - BUTTON_WIDTH, ((m / 3) * MAP_BUTTON_HEIGHT) + ((m / 3) * 5), MAP_BUTTON_WIDTH, MAP_BUTTON_HEIGHT, 20, background_color, sf::Color::Black, (*maps)[m / 3]));
                                                                        loading_map_body_button_list.push(new Button(((Config::SCREEN_WIDTH / 2) + (MAP_BUTTON_WIDTH / 2)) - BUTTON_WIDTH, ((m / 3)* MAP_BUTTON_HEIGHT) + ((m / 3) * 5), BUTTON_WIDTH, MAP_BUTTON_HEIGHT, 20, sf::Color(0,150,0), sf::Color::White, "Edit"));
                                                                        loading_map_body_button_list.push(new Button(((Config::SCREEN_WIDTH / 2) + (MAP_BUTTON_WIDTH / 2)), ((m / 3)* MAP_BUTTON_HEIGHT) + ((m / 3) * 5), BUTTON_WIDTH, MAP_BUTTON_HEIGHT, 20, sf::Color::Red, sf::Color::White, "Delete"));
                                                                        // Assign the load function
                                                                        (*loading_map_body_button_list.get_buttons())[m]->set_function([&game_state, &e, &d, &buffer_direction, &intended_direction, maps, m, &loading_map_body_button_list]()
                                                                        {                        
                                                                            e.initilize(Config::MAP_DIR + (*maps)[m / 3]);
                                                                            // If there was no error when initilizng the engine
                                                                            if (!e.get_alert()->is_toggled()){
                                                                                d.initilize_textures(e.get_board());                                                                       
                                                                                buffer_direction = e.get_character(characters::PACMAN)->get_direction();
                                                                                intended_direction = buffer_direction;
                                                                                e.get_ai()->move_all(&d, e.get_state_manager(), e.get_speed_manager());                                                                     
                                                                                game_state = game_states::PLAYING; 
                                                                            }
                                                                           
                                                                            });
                                                                        // Assign the edit function 
                                                                        (*loading_map_body_button_list.get_buttons())[m + 1]->set_function([maps, m, &game_state, &d, &e]()
                                                                        {  
                                                                            e.get_map_editor()->file_to_array(Config::MAP_DIR + (*maps)[m / 3]);
                                                                            d.initilize_textures(e.get_map_editor()->get_board());
                                                                            game_state = game_states::EDITING; 
                                                                        });
                                                                        // Assign the delete function
                                                                        (*loading_map_body_button_list.get_buttons())[m + 2]->set_function([maps, m, &game_state, &e]()
                                                                        {  
                                                                            int count = e.get_map_editor()->find_int_substring(Config::MAP_DIR + (*maps)[m / 3]);
                                                                            std::remove((Config::MAP_DIR + (*maps)[m / 3]).c_str());
                                                                            rapidjson::Document *document = Json::get_document(Config::JSON_DIR + "map_count.json");
                                                                            rapidjson::Value *array = Json::get_object(document, "taken_maps");
                                                                            Json::remove_int_from_array(Config::JSON_DIR + "map_count.json", document, array, count);
                                                                            Json::set_int(Config::JSON_DIR + "map_count.json", "count", Json::get_int(Config::JSON_DIR + "map_count.json", "count") -1);
                                                                            delete document;
                                                                            game_state = game_states::NO_MAP;
                                                                        });
                                                                    } });

    (*playing_footer_button_list.get_buttons())[1]->set_function([&game_state, &e, &loading_config_body_button_list, &d, &MAP_BUTTON_WIDTH, &BUTTON_HEIGHT, &BUTTON_WIDTH, &MAP_BUTTON_HEIGHT]()
                                                                 { game_state = game_states::LOADING_CONFIG; 
                                                                 std::vector<std::string> *configs = e.get_map_editor()->config_files(); 
                                                                 loading_config_body_button_list.clear();
                                                                 for (int m = 0; m < (*configs).size() * 3; m+=3){      
                                                                        sf::Color background_color; 
                                                                        (m / 3) % 2 == 0 ? background_color = sf::Color(224, 224, 224) : background_color = sf::Color(160, 160, 160);
                                                            
                                                                        loading_config_body_button_list.push(new Button(((Config::SCREEN_WIDTH / 2) - (MAP_BUTTON_WIDTH / 2)) - BUTTON_WIDTH, ((m / 3) * MAP_BUTTON_HEIGHT) + ((m / 3) * 5), MAP_BUTTON_WIDTH, MAP_BUTTON_HEIGHT, 20, background_color, sf::Color::Black, (*configs)[m / 3]));
                                                                        loading_config_body_button_list.push(new Button(((Config::SCREEN_WIDTH / 2) + (MAP_BUTTON_WIDTH / 2)) - BUTTON_WIDTH, ((m / 3)* MAP_BUTTON_HEIGHT) + ((m / 3) * 5), BUTTON_WIDTH, MAP_BUTTON_HEIGHT, 20, sf::Color(0,150,0), sf::Color::White, "Edit"));
                                                                        loading_config_body_button_list.push(new Button(((Config::SCREEN_WIDTH / 2) + (MAP_BUTTON_WIDTH / 2)), ((m / 3)* MAP_BUTTON_HEIGHT) + ((m / 3) * 5), BUTTON_WIDTH, MAP_BUTTON_HEIGHT, 20, sf::Color::Red, sf::Color::White, "Delete"));

                                                                        // Assign the delete function
                                                                        (*loading_config_body_button_list.get_buttons())[m + 2]->set_function([configs, m, &game_state, &e]()
                                                                        {  
                                                                            int count = e.get_map_editor()->find_int_substring(Config::MAP_DIR + (*configs)[m / 3]);
                                                                            std::remove(("config/" + (*configs)[m / 3]).c_str());
                                                                            Json::set_int(Config::JSON_DIR + "default_config.json", "count", Json::get_int(Config::JSON_DIR + "default_config.json", "count") - 1);
                                                                            game_state = game_states::NO_MAP;
                                                                        });
                                                                } });

    while (window.isOpen())
    {
        if (game_state == game_states::PLAYING)
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

                    e.get_navigation()->move(&d, e.get_character(characters::PACMAN), e.get_board(), direction, e.get_points(), &powerup);

                    // If a power pellet was eaten
                    if (powerup == power_types::POWER_PELLET)
                    {
                        // If a ghost was not already eaten, set its speed to slow down
                        for (int ghost = 0; ghost < 4; ghost++)
                        {
                            if (e.get_state_manager()->get_ghost_state(ghost) != ghost_states::HEADING_BACK)
                            {

                                if (e.get_state_manager()->get_ghost_mode() != ghost_modes::FRIGHTENED)
                                {

                                    e.get_speed_manager()->set_threshold(ghost, Config::FRIGHTENED_GHOST_SPEED);
                                    e.get_state_manager()->get_ghost_state_clock(ghost)->restart();
                                    e.get_state_manager()->get_ghost_state_clock(ghost)->set_threshold(Config::FRIGHTENED_TIME);
                                    e.get_state_manager()->get_ghost_state_clock(ghost)->delay_a_function([ghost, &e]()
                                                                                                          { e.get_speed_manager()->update_ghost_speed(ghost, e.get_speed_manager()->get_initial_time(type::GHOST)); });
                                }
                                else
                                {
                                    e.get_state_manager()->get_ghost_state_clock(ghost)->restart(false);
                                }
                            }
                        }
                        e.get_state_manager()->overide_mode(Config::FRIGHTENED_TIME, ghost_modes::FRIGHTENED);
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
                    buffer_direction = e.get_character(characters::PACMAN)->get_direction();
                    intended_direction = buffer_direction;
                    e.get_state_manager()->reset();

                    // If pacman has ran out of lives
                    if (e.get_life_manager()->is_game_over())
                    {
                        e.get_alert()->set_text("Game Over!");
                        e.get_alert()->set_toggled(true);
                        game_state = game_states::NO_MAP;
                    }
                }
                // Else if pacman has eaten a ghost
                else
                {
                    std::vector<Occupant *> occupants = (*(e.get_board()->get_board()))[e.get_character(characters::PACMAN)->get_x_position()][e.get_character(characters::PACMAN)->get_y_position()].get_all_occupants(type::GHOST);
                    for (Occupant *occupant : occupants)
                    {
                        e.get_state_manager()->set_ghost_state(static_cast<Ghost *>(occupant)->get_type(), ghost_states::HEADING_BACK);
                        e.get_points()->update(200);
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
                        e.get_ai()->move_based_on_state(&d, e.get_state_manager(), e.get_speed_manager(), ghost, true);
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
            if (event.type == sf::Event::TextEntered)
            {
                if (game_state == game_states::SELECTING_SIZE)
                {
                    int selected = selecting_size_body_input_list.get_selected();
                    if (selected != -1)
                    {
                        // If the number is a backspace and input is not empty
                        if (event.text.unicode == '\b' && (*selecting_size_body_input_list.get_inputs())[selected]->get_length_of_text() > 0)
                        {
                            (*selecting_size_body_input_list.get_inputs())[selected]->delete_character();
                        }
                        // If the input is a number and less than 4 characters
                        else if (event.text.unicode >= 48 && event.text.unicode <= 57 && (*selecting_size_body_input_list.get_inputs())[selected]->get_length_of_text() < 2)
                        {
                            (*selecting_size_body_input_list.get_inputs())[selected]->update_text(event.text.unicode);
                        }
                    }
                }
                else if (game_state == game_states::SELECTING_CONFIG_NAME)
                {
                    int selected = selecting_config_name_body_input_list.get_selected();
                    if (selected != -1)
                    {
                        // If the number is a backspace and input is not empty
                        if (event.text.unicode == '\b' && (*selecting_config_name_body_input_list.get_inputs())[selected]->get_length_of_text() > 0)
                        {
                            (*selecting_config_name_body_input_list.get_inputs())[selected]->delete_character();
                        }
                        // If the input is a number or letter and less than 8 characters
                        else if ((event.text.unicode >= 48 && event.text.unicode <= 57 || event.text.unicode >= 97 && event.text.unicode <= 122 || event.text.unicode >= 65 && event.text.unicode <= 90) && (*selecting_config_name_body_input_list.get_inputs())[selected]->get_length_of_text() < 8)
                        {
                            (*selecting_config_name_body_input_list.get_inputs())[selected]->update_text(event.text.unicode);
                        }
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (game_state == game_states::PLAYING)
                {
                    bool *moves = e.get_navigation()->get_possible_moves(e.get_character(characters::PACMAN), e.get_board());

                    if (event.key.code == sf::Keyboard::W)
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
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                float x = sf::Mouse::getPosition(window).x;
                float y = sf::Mouse::getPosition(window).y;

                if (e.get_alert()->is_toggled())
                {
                    y -= Config::HEADER_HEIGHT;
                    if (e.get_alert()->get_dismiss_button()->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                    {
                        e.get_alert()->set_toggled(false);
                    }
                }

                else if (game_state == game_states::SELECTING_SIZE)
                {
                    for (int b = 0; b < (*selecting_size_header_button_list.get_buttons()).size(); b++)
                    {
                        if ((*selecting_size_header_button_list.get_buttons())[b]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            (*selecting_size_header_button_list.get_buttons())[b]->run_function();
                        }
                    }
                    y -= Config::HEADER_HEIGHT;
                    for (int i = 0; i < (*selecting_size_body_input_list.get_inputs()).size(); i++)
                    {
                        if ((*selecting_size_body_input_list.get_inputs())[i]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            selecting_size_body_input_list.set_selected(i);
                        }
                    }
                }

                else if (game_state == game_states::LOADING_MAP)
                {
                    for (int b = 0; b < (*loading_map_header_button_list.get_buttons()).size(); b++)
                    {
                        if ((*loading_map_header_button_list.get_buttons())[b]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            (*loading_map_header_button_list.get_buttons())[b]->run_function();
                        }
                    }
                    y -= Config::HEADER_HEIGHT;
                    for (int b = 0; b < (*loading_map_body_button_list.get_buttons()).size(); b++)
                    {
                        if ((*loading_map_body_button_list.get_buttons())[b]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            (*loading_map_body_button_list.get_buttons())[b]->run_function();
                        }
                    }
                }

                else if (game_state == game_states::LOADING_CONFIG)
                {
                    y -= Config::HEADER_HEIGHT + Config::BODY_HEIGHT;
                    for (int b = 0; b < (*loading_config_footer_button_list.get_buttons()).size(); b++)
                    {
                        if ((*loading_config_footer_button_list.get_buttons())[b]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            (*loading_config_footer_button_list.get_buttons())[b]->run_function();
                        }
                    }

                    y += Config::BODY_HEIGHT;

                    for (int b = 0; b < (*loading_config_body_button_list.get_buttons()).size(); b++)
                    {
                        if ((*loading_config_body_button_list.get_buttons())[b]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            (*loading_config_body_button_list.get_buttons())[b]->run_function();
                        }
                    }
                }

                else if (game_state == game_states::PLAYING || game_state == game_states::NO_MAP)
                {
                    for (int b = 0; b < (*playing_header_button_list.get_buttons()).size(); b++)
                    {
                        if ((*playing_header_button_list.get_buttons())[b]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            (*playing_header_button_list.get_buttons())[b]->run_function();
                        }
                    }

                    y -= Config::HEADER_HEIGHT + Config::BODY_HEIGHT;

                    for (int b = 0; b < (*playing_footer_button_list.get_buttons()).size(); b++)
                    {

                        if ((*playing_footer_button_list.get_buttons())[b]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            (*playing_footer_button_list.get_buttons())[b]->run_function();
                        }
                    }
                }
                else if (game_state == game_states::SELECTING_CONFIG_NAME)
                {
                    y -= Config::HEADER_HEIGHT + Config::BODY_HEIGHT;

                    for (int b = 0; b < (*selecting_config_name_footer_button_list.get_buttons()).size(); b++)
                    {

                        if ((*selecting_config_name_footer_button_list.get_buttons())[b]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            (*selecting_config_name_footer_button_list.get_buttons())[b]->run_function();
                        }
                    }

                    y += Config::BODY_HEIGHT;
                    for (int i = 0; i < (*selecting_config_name_body_input_list.get_inputs()).size(); i++)
                    {
                        if ((*selecting_config_name_body_input_list.get_inputs())[i]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            selecting_config_name_body_input_list.set_selected(i);
                        }
                    }
                }
                else if (game_state == game_states::EDITING)
                {

                    for (int b = 0; b < (*editing_header_button_list.get_buttons()).size(); b++)
                    {
                        if ((*editing_header_button_list.get_buttons())[b]->get_cell()->getGlobalBounds().contains(sf::Vector2f(x, y)))
                        {
                            (*editing_header_button_list.get_buttons())[b]->run_function();
                        }
                    }

                    y -= (Config::HEADER_HEIGHT + Config::BODY_HEIGHT);
                    for (int i = 0; i < e.get_map_editor()->get_tile_set()->size(); i++)
                    {
                        if ((*(e.get_map_editor()->get_tile_set()))[i].get_rect().getGlobalBounds().contains(x, y))
                        {
                            e.get_map_editor()->select_tile(x, y);
                        }
                    }

                    y += Config::BODY_HEIGHT;
                    if (y >= 0 && y <= Config::BODY_HEIGHT)
                    {
                        e.get_map_editor()->add_tile(&d, x, y);
                    }
                }
            }
        }

        d.clear_all();

        if (game_state == game_states::PLAYING)
        {
            d.draw_board(e.get_board());

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

                e.get_ai()->move_all(&d, e.get_state_manager(), e.get_speed_manager());

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

            d.draw_buttons(playing_header_button_list.get_buttons(), texture_surfaces::HEADER);
            d.draw_buttons(playing_footer_button_list.get_buttons(), texture_surfaces::FOOTER);
            d.draw_score(e.get_points());

            if (e.get_points()->has_won())
            {
                int n_points = e.get_points()->get_n_points();
                int n_lives = e.get_life_manager()->get_n_lives();
                e.initilize(e.get_map_editor()->get_open_map());
                e.get_points()->update(n_points);
                e.get_life_manager()->set_n_lives(n_lives);
                d.initilize_textures(e.get_board());
                e.get_ai()->move_all(&d, e.get_state_manager(), e.get_speed_manager());
            }
            d.draw_lives(e.get_life_manager()->get_n_lives());
        }
        else if (game_state == game_states::EDITING)
        {
            d.draw_board(e.get_map_editor()->get_board(), true);
            d.draw_tiles(e.get_map_editor()->get_tile_set(), e.get_map_editor()->get_selected_tile());
            d.draw_buttons(editing_header_button_list.get_buttons(), texture_surfaces::HEADER);
        }
        else if (game_state == game_states::NO_MAP)
        {
            d.draw_buttons(playing_header_button_list.get_buttons(), texture_surfaces::HEADER);
            d.draw_buttons(playing_footer_button_list.get_buttons(), texture_surfaces::FOOTER);
        }
        else if (game_state == game_states::LOADING_MAP)
        {
            d.draw_buttons(loading_map_header_button_list.get_buttons(), texture_surfaces::HEADER);
            d.draw_buttons(loading_map_body_button_list.get_buttons(), texture_surfaces::BODY);
        }
        else if (game_state == game_states::LOADING_CONFIG)
        {
            d.draw_buttons(loading_config_body_button_list.get_buttons(), texture_surfaces::BODY);
            d.draw_buttons(loading_config_footer_button_list.get_buttons(), texture_surfaces::FOOTER);
        }
        else if (game_state == game_states::SELECTING_SIZE)
        {
            d.draw_buttons(selecting_size_header_button_list.get_buttons(), texture_surfaces::HEADER);
            d.draw_inputs(selecting_size_body_input_list.get_inputs(), selecting_size_body_input_list.get_selected(), texture_surfaces::BODY);
        }
        else if (game_state == game_states::SELECTING_CONFIG_NAME)
        {
            d.draw_buttons(selecting_config_name_footer_button_list.get_buttons(), texture_surfaces::FOOTER);
            d.draw_inputs(selecting_config_name_body_input_list.get_inputs(), selecting_config_name_body_input_list.get_selected(), texture_surfaces::BODY);
        }

        d.draw_alert(e.get_alert());
        d.draw_all();
    }

    return 0;
}