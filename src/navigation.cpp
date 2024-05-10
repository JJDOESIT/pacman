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

            // Note: This case where no moves are valid shouldn't happen. But if it does, then
            //       set the ghost to move back the way it came.
            bool no_moves = true;
            for (int move = 0; move < 4; move++)
            {
                if (moves[move])
                {
                    no_moves = false;
                }
            }
            if (no_moves)
            {
                if (occupant->get_direction() == moves::UP)
                {
                    moves[moves::DOWN] = true;
                }
                else if (occupant->get_direction() == moves::DOWN)
                {
                    moves[moves::UP] = true;
                }
                else if (occupant->get_direction() == moves::LEFT)
                {
                    moves[moves::RIGHT] = true;
                }
                else if (occupant->get_direction() == moves::RIGHT)
                {
                    moves[moves::LEFT] = true;
                }
            }
        }
    }
    return moves;
}

// Move a player or ghost a given direction
void Navigation::move_occupant(Draw_Manager *draw_manager, Occupant *occupant, Board *board, int direction, Points *points, int *powerup)
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
                points->decreament_coins();
                draw_manager->set_texture(*coin->get_cell(), coin->get_type(), 0, false);
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
                    points->update(50);
                    *powerup = power_types::POWER_PELLET;
                    draw_manager->set_texture(*power->get_cell(), type::POWER, static_cast<Power *>(power)->get_type(), false);
                }
            }
        }
    }
}

// User interface class to move a given occupant a given direction
void Navigation::move(Draw_Manager *draw_manager, Occupant *occupant, Board *board, int direction, Points *points, int *powerup)
{
    if (occupant)
    {
        bool *moves = get_possible_moves(occupant, board);

        if (moves[direction])
        {
            move_occupant(draw_manager, occupant, board, direction, points, powerup);
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
        occupant->set_direction(static_cast<Pacman *>(occupant)->get_initial_direction());
        (*board->get_board())[occupant->get_x_position()][occupant->get_y_position()].push(occupant);
    }
    else if (occupant->get_type() == type::GHOST)
    {
        (*board->get_board())[occupant->get_x_position()][occupant->get_y_position()].pop_specific_occupant(occupant);
        occupant->set_position(static_cast<Ghost *>(occupant)->get_initial_x(), static_cast<Ghost *>(occupant)->get_initial_y());
        occupant->set_direction(static_cast<Ghost *>(occupant)->get_initial_direction());
        (*board->get_board())[occupant->get_x_position()][occupant->get_y_position()].push(occupant);
    }
}

// Reset the position and direction of the characters
void Navigation::reset_all_characters(Board *board, Occupant **characters)
{
    for (int character = 0; character < 5; character++)
    {
        if (characters[character])
        {
            reset_position(board, characters[character]);
            if (character == characters::PACMAN)
            {
                characters[character]->set_direction(static_cast<Pacman *>(characters[character])->get_initial_direction());
            }
            else
            {
                characters[character]->set_direction(static_cast<Ghost *>(characters[character])->get_initial_direction());
            }
        }
    }
}
