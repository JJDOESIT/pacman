#include "ai.h"

AI::AI(Board *b, Navigation *n, Occupant *characters[5])
{
    AI::b = b;
    AI::n = n;
    AI::characters[characters::BLINKY] = characters[characters::BLINKY];
    AI::characters[characters::PINKY] = characters[characters::PINKY];
    AI::characters[characters::INKY] = characters[characters::INKY];
    AI::characters[characters::CLYDE] = characters[characters::CLYDE];
    AI::characters[characters::PACMAN] = characters[characters::PACMAN];
}

AI::~AI()
{
}

// Calculate the euclidean distance between two given points
int AI::euclidean_distance(int x1, int y1, int x2, int y2)
{
    return std::pow(std::abs(x1 - x2), 2) + std::pow(std::abs(y1 - y2), 2);
}

// Given an occupant, and a target tile, return the shortest direction (up, left, right, down)
// that will bring the occupant closer to the target tile
int AI::best_direction(bool moves[], Occupant *occupant, int target_x, int target_y)
{
    int tie_breaker[4] = {0, 4, 2, 1};
    int shortest_distance = -1;
    int shortest_direction = -1;

    for (int i = 0; i < 4; i++)
    {
        if (moves[i])
        {
            int x = occupant->get_x_position();
            int y = occupant->get_y_position();

            int d = euclidean_distance(x + linear_directions_one[i][0], y + linear_directions_one[i][1], target_x, target_y);

            // If the shortest direction hasn't been set yet (first iteration of the loop)
            if (shortest_direction == -1)
            {
                shortest_distance = d;
                shortest_direction = i;
            }
            // If a shorter path has been found
            else if (d < shortest_distance)
            {
                shortest_distance = d;
                shortest_direction = i;
            }
            // If two path's are the same distance, break the tie using order of precedence
            else if (d == shortest_distance)
            {
                if (tie_breaker[i] < tie_breaker[shortest_direction])
                {
                    shortest_direction = i;
                }
            }
        }
    }
    return shortest_direction;
}

// Handle the ghost's scatter behaivor
void AI::scatter(int ghost)
{
    Occupant *occupant = characters[ghost];
    bool *moves = n->get_possible_moves(occupant, b);

    int target_x = static_cast<Ghost *>(occupant)->get_target_x_tile();
    int target_y = static_cast<Ghost *>(occupant)->get_target_y_tile();

    int direction = best_direction(moves, occupant, target_x, target_y);

    static_cast<Ghost *>(occupant)->set_best_move(occupant->get_x_position() + linear_directions_one[direction][0], occupant->get_y_position() + linear_directions_one[direction][1]);
    occupant->set_direction(direction);

    delete[] moves;
}

// Handle blinky's chase mode
void AI::blinky_ai(int ghost)
{
    Occupant *blinky = characters[ghost];
    bool *moves = n->get_possible_moves(blinky, b);

    // Set blinky's target tile to be pacman's position
    int target_x = static_cast<Pacman *>(characters[characters::PACMAN])->get_x_position();
    int target_y = static_cast<Pacman *>(characters[characters::PACMAN])->get_y_position();

    int direction = best_direction(moves, blinky, target_x, target_y);

    static_cast<Ghost *>(blinky)->set_best_move(blinky->get_x_position() + linear_directions_one[direction][0], blinky->get_y_position() + linear_directions_one[direction][1]);
    blinky->set_direction(direction);

    delete[] moves;
}

// Handle pinky's chase mode
void AI::pinky_ai(int ghost)
{
    Occupant *pinky = characters[ghost];
    bool *moves = n->get_possible_moves(pinky, b);

    int target_x = static_cast<Pacman *>(characters[characters::PACMAN])->get_x_position();
    int target_y = static_cast<Pacman *>(characters[characters::PACMAN])->get_y_position();

    // Set pinky's target tile to be four spaces ahead of pacman
    target_x += linear_directions_four[static_cast<Pacman *>(characters[characters::PACMAN])->get_direction()][0];
    target_y += linear_directions_four[static_cast<Pacman *>(characters[characters::PACMAN])->get_direction()][1];

    int direction = best_direction(moves, pinky, target_x, target_y);

    static_cast<Ghost *>(pinky)->set_best_move(pinky->get_x_position() + linear_directions_one[direction][0], pinky->get_y_position() + linear_directions_one[direction][1]);
    pinky->set_direction(direction);

    delete[] moves;
}

// Handle inky's chase mode
void AI::inky_ai(int ghost)
{
    Occupant *inky = characters[ghost];
    bool *moves = n->get_possible_moves(inky, b);

    int target_x = static_cast<Pacman *>(characters[characters::PACMAN])->get_x_position();
    int target_y = static_cast<Pacman *>(characters[characters::PACMAN])->get_y_position();

    // Find the space two ahead of pacman's current direction
    target_x += linear_directions_two[static_cast<Pacman *>(characters[characters::PACMAN])->get_direction()][0];
    target_y += linear_directions_two[static_cast<Pacman *>(characters[characters::PACMAN])->get_direction()][1];

    // Calculate the x and y distances between the space two ahead of pacman
    // and blinky
    int x_distance = std::abs(characters[characters::BLINKY]->get_x_position() - target_x);
    int y_distance = std::abs(characters[characters::BLINKY]->get_y_position() - target_y);

    // Set inky to move towards the best route that will bring him closer to his target tile
    // (target tile is double the vector of x_distance and y_distance)
    int direction = best_direction(moves, inky, target_x + x_distance, target_y + y_distance);

    static_cast<Ghost *>(inky)->set_best_move(inky->get_x_position() + linear_directions_one[direction][0], inky->get_y_position() + linear_directions_one[direction][1]);
    inky->set_direction(direction);

    delete[] moves;
}

// Handle clyde's chase mode
void AI::clyde_ai(int ghost)
{
    Occupant *clyde = characters[ghost];
    bool *moves = n->get_possible_moves(clyde, b);

    int target_x = static_cast<Pacman *>(characters[characters::PACMAN])->get_x_position();
    int target_y = static_cast<Pacman *>(characters[characters::PACMAN])->get_y_position();

    int distance = euclidean_distance(clyde->get_x_position(), clyde->get_y_position(), target_x, target_y);

    // If clyde is within 8 tiles of pacman, he will scatter to his tile
    // else he will target pacman's current position (exactly the same as blinky)
    if (distance <= 64)
    {
        scatter(ghosts_types::CLYDE);
    }
    else
    {
        blinky_ai(ghosts_types::CLYDE);
    }

    delete[] moves;
}

// Set the occupant to the farthest tile away from pacman
void AI::run(int ghost)
{
    Occupant *occupant = characters[ghost];
    bool *moves = n->get_possible_moves(occupant, b);

    int tie_breaker[4] = {0, 4, 2, 1};
    int longest_distance = -1;
    int longest_direction = -1;

    // Calulcate the direction that would place the occupant farthest from pacman's position
    for (int i = 0; i < 4; i++)
    {
        if (moves[i])
        {
            int x = occupant->get_x_position();
            int y = occupant->get_y_position();

            int d = euclidean_distance(x + linear_directions_one[i][0], y + linear_directions_one[i][1], characters[characters::PACMAN]->get_x_position(), characters[characters::PACMAN]->get_y_position());

            // If the shortest direction hasn't been set yet (first iteration of the loop)
            if (longest_direction == -1)
            {
                longest_distance = d;
                longest_direction = i;
            }
            // If a shorter path has been found
            else if (d > longest_distance)
            {
                longest_distance = d;
                longest_direction = i;
            }
            // If two path's are the same distance, break the tie using order of precedence
            else if (d == longest_distance)
            {
                if (tie_breaker[i] > tie_breaker[longest_direction])
                {
                    longest_direction = i;
                }
            }
        }
    }

    static_cast<Ghost *>(occupant)->set_best_move(occupant->get_x_position() + linear_directions_one[longest_direction][0], occupant->get_y_position() + linear_directions_one[longest_direction][1]);
    occupant->set_direction(longest_direction);

    delete[] moves;
}

// Assign a ghost to move in it's current direction
void AI::move_in_current_direction(int ghost)
{
    Occupant *occupant = characters[ghost];
    static_cast<Ghost *>(occupant)->set_best_move(occupant->get_x_position() + linear_directions_one[occupant->get_direction()][0], occupant->get_y_position() + linear_directions_one[occupant->get_direction()][1]);
}

// Find the direction that will bring the ghost closer to its escape tile
void AI::move_to_escape_tile(State_Manager *state_manager, int ghost)
{
    Occupant *occupant = characters[ghost];
    bool *moves = n->get_possible_moves(occupant, b);

    int direction = best_direction(moves, occupant, state_manager->get_ghost_escape_x(ghost), state_manager->get_ghost_escape_y(ghost));

    static_cast<Ghost *>(occupant)->set_best_move(occupant->get_x_position() + linear_directions_one[direction][0], occupant->get_y_position() + linear_directions_one[direction][1]);
    occupant->set_direction(direction);

    delete[] moves;
}

// Return the ghost to its initial starting position
void AI::return_to_start(State_Manager *state_manager, int ghost)
{
    Occupant *occupant = characters[ghost];
    bool *moves = n->get_possible_moves(occupant, b);

    int direction = best_direction(moves, occupant, state_manager->get_ghost_escape_x(ghost), state_manager->get_ghost_escape_y(ghost));

    static_cast<Ghost *>(occupant)->set_best_move(occupant->get_x_position() + linear_directions_one[direction][0], occupant->get_y_position() + linear_directions_one[direction][1]);
    occupant->set_direction(direction);

    delete[] moves;
}

// Move ghosts based on their current state and mode
void AI::move_based_on_state(State_Manager *state_manager, Ghost_Clocks *ghost_clocks, int ghost)
{
    Occupant *occupant = characters[ghost];

    // If the ghost is not nullptr
    if (occupant && state_manager->get_ghost_state(ghost) != ghost_states::DISABLED)
    {
        // If the ghost is escaping the den
        if (state_manager->get_ghost_state(ghost) == ghost_states::ESCAPING)
        {
            // If the ghost has just entered the escape tile (their assigned gate)
            if (state_manager->has_escaped(occupant))
            {
                // Move them once more in their current direction
                move_in_current_direction(ghost);
                state_manager->set_ghost_state(ghost, ghost_states::FREE);
            }
            // Else if the ghost is still moving to their gate
            else
            {
                move_to_escape_tile(state_manager, ghost);
            }
        }
        // Else if the ghost has been eaten, and is heading back
        else if (state_manager->get_ghost_state(ghost) == ghost_states::HEADING_BACK)
        {
            // If the ghost has just entered the escape tile (their assigned gate)
            if (state_manager->has_escaped(occupant))
            {
                // Move them once more in their current direction
                move_in_current_direction(ghost);
                state_manager->set_ghost_state(ghost, ghost_states::ESCAPING);
                state_manager->overide_state(7000, ghost_states::DISABLED, ghost);
                ghost_clocks->clocks[ghost]->set_threshold(ghost_clocks->clocks[ghost]->get_initial_time());
            }
            // Else if the ghost is still heading back
            else
            {
                return_to_start(state_manager, ghost);
            }
        }
        // Else if the ghost is chasing pacman
        else if (state_manager->get_ghost_mode() == ghost_modes::CHASE)
        {
            if (ghost == ghosts_types::BLINKY)
            {
                blinky_ai(ghost);
            }
            else if (ghost == ghosts_types::PINKY)
            {
                pinky_ai(ghost);
            }
            else if (ghost == ghosts_types::INKY)
            {
                // Note: This is needed because if blinky doesn't exist, we cannot call inky's
                //       AI function as he is dependent on blinky's position. In this case,
                //       inky will instead act like blinky, and chase pacman directly.
                if (characters[characters::BLINKY])
                {
                    inky_ai(ghost);
                }
                else
                {
                    blinky_ai(ghost);
                }
            }
            else if (ghost == ghosts_types::CLYDE)
            {
                clyde_ai(ghost);
            }
        }
        // Else if the ghost is in scatter mode
        else if (state_manager->get_ghost_mode() == ghost_modes::SCATTER)
        {
            scatter(ghost);
        }
        // Else if the ghosts are running away from pacman
        else if (state_manager->get_ghost_mode() == ghost_modes::FRIGHTENED)
        {
            run(ghost);
        }
    }
}

// Move all ghosts
void AI::move_all(State_Manager *state_manager, Ghost_Clocks *ghost_clocks)
{
    move_based_on_state(state_manager, ghost_clocks, ghosts_types::BLINKY);
    move_based_on_state(state_manager, ghost_clocks, ghosts_types::PINKY);
    move_based_on_state(state_manager, ghost_clocks, ghosts_types::INKY);
    move_based_on_state(state_manager, ghost_clocks, ghosts_types::CLYDE);
}
