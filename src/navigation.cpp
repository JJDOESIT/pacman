#include "navigation.h"

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
            if ((*board->get_board())[x + 1][y].find_occupant(type::WALL) == nullptr)
            {
                moves[moves::DOWN] = true;
            }
        }
        // Check if the ghost can move up
        if (x - 1 >= 0 && occupant->get_direction() != moves::DOWN)
        {
            if ((*board->get_board())[x - 1][y].find_occupant(type::WALL) == nullptr)
            {
                moves[moves::UP] = true;
            }
        }
        // Check if the ghost can move right
        if (y + 1 < board->get_cols() && occupant->get_direction() != moves::LEFT)
        {
            if ((*board->get_board())[x][y + 1].find_occupant(type::WALL) == nullptr)
            {
                moves[moves::RIGHT] = true;
            }
        }
        // Check if the ghost can move left
        if (y - 1 >= 0 && occupant->get_direction() != moves::RIGHT)
        {
            if ((*board->get_board())[x][y - 1].find_occupant(type::WALL) == nullptr)
            {
                moves[moves::LEFT] = true;
            }
        }
    }
    return moves;
}

// Move a player or ghost a given direction
void Navigation::move_occupant(Occupant *occupant, Board *board, int direction, Points *points)
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
        int linear_directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        row = static_cast<Portal *>(portal)->get_link()->get_x_position() + linear_directions[portal->get_direction()][0];
        col = static_cast<Portal *>(portal)->get_link()->get_y_position() + linear_directions[portal->get_direction()][1];

        occupant->set_position(row, col);
    }

    // Push the occupant into the new position on the board
    (*board->get_board())[row][col].push(occupant);

    // Determine whether pacman has entered a space with a coin in it (If he has, toggle off the coin)
    if (occupant->get_type() == type::PLAYER)
    {
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
    }
}

// User interface class to move a given occupant a given direction
void Navigation::move(Occupant *occupant, Board *board, int direction, Points *points)
{
    bool *moves = get_possible_moves(occupant, board);

    if (moves[direction])
    {
        move_occupant(occupant, board, direction, points);
    }

    delete[] moves;
}

// Move all ghost's
void Navigation::move_all_ghosts(Board *board, Occupant *blinky, Occupant *pinky, Occupant *inky, Occupant *clyde)
{
    if (blinky)
    {
        move(blinky, board, blinky->get_direction());
    }
    if (pinky)
    {
        move(pinky, board, pinky->get_direction());
    }
    if (inky)
    {
        move(inky, board, inky->get_direction());
    }
    if (clyde)
    {
        move(clyde, board, clyde->get_direction());
    }
}
