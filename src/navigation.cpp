#include "navigation.h"

Navigation::Navigation(State_Manager *state_manager)
{
    Navigation::state_manager = state_manager;
}

// Return a bool array of possible moves the occupant can make
bool *Navigation::get_possible_moves(Occupant *occupant, Board *board)
{
    bool *moves = new bool[4]();
    int x = occupant->get_x_position();
    int y = occupant->get_y_position();

    if (occupant->get_type() == type::PLAYER)
    {
        // Check if the player can move down
        if (x + 1 < board->get_rows())
        {
            if ((*board->get_board())[x + 1][y].find_occupant(type::WALL) == nullptr)
            {
                moves[moves::DOWN] = true;
            }
        }
        // Check if the player can move up
        if (x - 1 >= 0)
        {
            if ((*board->get_board())[x - 1][y].find_occupant(type::WALL) == nullptr)
            {
                moves[moves::UP] = true;
            }
        }
        // Check if the player can move right
        if (y + 1 < board->get_cols())
        {
            if ((*board->get_board())[x][y + 1].find_occupant(type::WALL) == nullptr)
            {
                moves[moves::RIGHT] = true;
            }
        }
        // Check if the player can move left
        if (y - 1 >= 0)
        {
            if ((*board->get_board())[x][y - 1].find_occupant(type::WALL) == nullptr)
            {
                moves[moves::LEFT] = true;
            }
        }
    }

    else if (occupant->get_type() == type::GHOST)
    {
        // Check if the ghost can move down
        if (x + 1 < board->get_rows() && occupant->get_direction() != moves::UP)
        {
            Occupant *wall = (*board->get_board())[x + 1][y].find_occupant(type::WALL);
            if (wall == nullptr)
            {
                moves[moves::DOWN] = true;
            }
            else if (static_cast<Wall *>(wall)->get_wall_type() == wall_type::GATE)
            {
                int state = state_manager->get_ghost_state(static_cast<Ghost *>(occupant)->get_type());
                if (state == ghost_states::ESCAPING || state == ghost_states::HEADING_BACK)
                {
                    if (state_manager->get_ghost_escape_x(static_cast<Ghost *>(occupant)->get_type()) == x + 1 && state_manager->get_ghost_escape_y(static_cast<Ghost *>(occupant)->get_type()) == y)
                    {
                        moves[moves::DOWN] = true;
                    }
                }
            }
        }
        // Check if the ghost can move up
        if (x - 1 >= 0 && occupant->get_direction() != moves::DOWN)
        {
            Occupant *wall = (*board->get_board())[x - 1][y].find_occupant(type::WALL);
            if (wall == nullptr)
            {
                moves[moves::UP] = true;
            }
            else if (static_cast<Wall *>(wall)->get_wall_type() == wall_type::GATE)
            {
                int state = state_manager->get_ghost_state(static_cast<Ghost *>(occupant)->get_type());
                if (state == ghost_states::ESCAPING || state == ghost_states::HEADING_BACK)
                {
                    if (state_manager->get_ghost_escape_x(static_cast<Ghost *>(occupant)->get_type()) == x - 1 && state_manager->get_ghost_escape_y(static_cast<Ghost *>(occupant)->get_type()) == y)
                    {
                        moves[moves::UP] = true;
                    }
                }
            }
        }
        // Check if the ghost can move right
        if (y + 1 < board->get_cols() && occupant->get_direction() != moves::LEFT)
        {
            Occupant *wall = (*board->get_board())[x][y + 1].find_occupant(type::WALL);
            if (wall == nullptr)
            {
                moves[moves::RIGHT] = true;
            }
            else if (static_cast<Wall *>(wall)->get_wall_type() == wall_type::GATE)
            {
                int state = state_manager->get_ghost_state(static_cast<Ghost *>(occupant)->get_type());
                if (state == ghost_states::ESCAPING || state == ghost_states::HEADING_BACK)
                {
                    if (state_manager->get_ghost_escape_x(static_cast<Ghost *>(occupant)->get_type()) == x && state_manager->get_ghost_escape_y(static_cast<Ghost *>(occupant)->get_type()) == y + 1)
                    {
                        moves[moves::RIGHT] = true;
                    }
                }
            }
        }
        // Check if the ghost can move left
        if (y - 1 >= 0 && occupant->get_direction() != moves::RIGHT)
        {
            Occupant *wall = (*board->get_board())[x][y - 1].find_occupant(type::WALL);
            if (wall == nullptr)
            {
                moves[moves::LEFT] = true;
            }
            else if (static_cast<Wall *>(wall)->get_wall_type() == wall_type::GATE)
            {
                int state = state_manager->get_ghost_state(static_cast<Ghost *>(occupant)->get_type());
                if (state == ghost_states::ESCAPING || state == ghost_states::HEADING_BACK)
                {
                    if (state_manager->get_ghost_escape_x(static_cast<Ghost *>(occupant)->get_type()) == x && state_manager->get_ghost_escape_y(static_cast<Ghost *>(occupant)->get_type()) == y - 1)
                    {
                        moves[moves::LEFT] = true;
                    }
                }
            }
        }
    }
    return moves;
}

// Move a player or ghost a given direction
void Navigation::move_occupant(Occupant *occupant, Board *board, int direction, Points *points, int *powerup)
{
    int row = occupant->get_x_position();
    int col = occupant->get_y_position();

    // Remove occupant from the current position on the board
    (*board->get_board())[row][col].pop_specific_occupant(occupant);

    // Update occupant's position if he moves up
    if (direction == moves::UP)
    {
        occupant->set_direction(moves::UP);
        occupant->set_position(row - 1, col);
        row--;
    }
    // Update occupant's position if he moves right
    else if (direction == moves::RIGHT)
    {
        occupant->set_direction(moves::RIGHT);
        occupant->set_position(row, col + 1);
        col++;
    }
    // Update occupant's position if he moves down
    else if (direction == moves::DOWN)
    {
        occupant->set_direction(moves::DOWN);
        occupant->set_position(row + 1, col);
        row++;
    }
    // Update occupant's position if he moves left
    else if (direction == moves::LEFT)
    {
        occupant->set_direction(moves::LEFT);
        occupant->set_position(row, col - 1);
        col--;
    }

    // Check if the occupant entered a portal
    if ((*board->get_board())[row][col].find_occupant(type::PORTAL))
    {

        Occupant *portal = (*board->get_board())[row][col].find_occupant(type::PORTAL);

        row = static_cast<Portal *>(portal)->get_link()->get_x_position() + linear_directions_one[portal->get_direction()][0];
        col = static_cast<Portal *>(portal)->get_link()->get_y_position() + linear_directions_one[portal->get_direction()][1];

        occupant->set_position(row, col);
    }

    // Push the occupant into the new position on the board
    (*board->get_board())[row][col].push(occupant);

    if (occupant->get_type() == type::PLAYER)
    {
        // Determine whether pacman has entered a space with a coin in it (If he has, toggle off the coin)
        Coin *coin = static_cast<Coin *>((*board->get_board())[row][col].find_occupant(type::COIN));
        // If a coin is found in the occupant list
        if (coin != nullptr)
        {
            // If the coin has not been eaten yet, toggle it off and increase score by 10
            if (coin->get_toggled())
            {
                coin->set_toggled(false);
                points->update(10);
            }
        }
        // Determine whether pacman has entered a space with a power up in it (If he has, return what type)
        Power *power = static_cast<Power *>((*board->get_board())[row][col].find_occupant(type::POWER));
        if (power != nullptr)
        {
            if (power->get_toggled())
            {
                if (power->get_type() == power_types::POWER_PELLET)
                {
                    power->set_toggled(false);
                    points->update(200);
                    *powerup = power_types::POWER_PELLET;
                }
            }
        }
    }
}

// User interface class to move a given occupant a given direction
void Navigation::move(Occupant *occupant, Board *board, int direction, Points *points, int *powerup)
{
    if (occupant)
    {
        bool *moves = get_possible_moves(occupant, board);

        if (moves[direction])
        {
            move_occupant(occupant, board, direction, points, powerup);
        }

        delete[] moves;
    }
}

// Reset the position of the given occupant
void Navigation::reset_position(Board *board, Occupant *occupant)
{

    if (occupant->get_type() == type::PLAYER)
    {
        (*board->get_board())[occupant->get_x_position()][occupant->get_y_position()].pop_specific_occupant(occupant);
        occupant->set_position(static_cast<Pacman *>(occupant)->get_initial_x(), static_cast<Pacman *>(occupant)->get_initial_y());
        (*board->get_board())[occupant->get_x_position()][occupant->get_y_position()].push(occupant);
    }
    else if (occupant->get_type() == type::GHOST)
    {
        (*board->get_board())[occupant->get_x_position()][occupant->get_y_position()].pop_specific_occupant(occupant);
        occupant->set_position(static_cast<Ghost *>(occupant)->get_initial_x(), static_cast<Ghost *>(occupant)->get_initial_y());
        (*board->get_board())[occupant->get_x_position()][occupant->get_y_position()].push(occupant);
    }
}

// Reset all positions
void Navigation::reset_all_positions(Board *board, Occupant **characters)
{
    if (characters[characters::PACMAN])
    {
        reset_position(board, characters[characters::PACMAN]);
    }
    if (characters[characters::BLINKY])
    {
        reset_position(board, characters[characters::BLINKY]);
    }
    if (characters[characters::PINKY])
    {
        reset_position(board, characters[characters::PINKY]);
    }
    if (characters[characters::INKY])
    {
        reset_position(board, characters[characters::INKY]);
    }
    if (characters[characters::CLYDE])
    {
        reset_position(board, characters[characters::CLYDE]);
    }
}
