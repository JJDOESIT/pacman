#include "navigation.h"

// Return a bool array of possible moves the occupant can make
bool *Navigation::get_possible_moves(Occupant *occupant, Board *board)
{
    bool *moves = new bool[4]();

    if (occupant->get_type() == type::PLAYER)
    {

        int x = occupant->get_x_position();
        int y = occupant->get_y_position();

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
    return moves;
}

// Move a player or ghost given a direction
void Navigation::move_occupant(Occupant *occupant, Board *board, int direction)
{
    if (occupant->get_type() == type::PLAYER)
    {
        int row = occupant->get_x_position();
        int col = occupant->get_y_position();

        // Remove pacman from his current position on the board
        (*board->get_board())[row][col].pop_occupant(type::PLAYER);

        // Update pacman's position if he moves up
        if (direction == moves::UP)
        {
            static_cast<Pacman *>(occupant)->set_direction(moves::UP);
            occupant->set_position(row - 1, col);
            row--;
        }
        // Update pacman's position if he moves right
        else if (direction == moves::RIGHT)
        {
            static_cast<Pacman *>(occupant)->set_direction(moves::RIGHT);
            occupant->set_position(row, col + 1);
            col++;
        }
        // Update pacman's position if he moves down
        else if (direction == moves::DOWN)
        {
            static_cast<Pacman *>(occupant)->set_direction(moves::DOWN);
            occupant->set_position(row + 1, col);
            row++;
        }
        // Update pacman's position if he moves left
        else if (direction == moves::LEFT)
        {
            static_cast<Pacman *>(occupant)->set_direction(moves::LEFT);
            occupant->set_position(row, col - 1);
            col--;
        }

        // Push pacman into his new position on the board
        (*board->get_board())[row][col].push(occupant);

        // Determine whether pacman has entered a space with a coin in it (If he has, toggle off the coin)
        Coin *coin = static_cast<Coin *>((*board->get_board())[row][col].find_occupant(type::COIN));
        if (coin != nullptr)
        {
            coin->set_toggled(false);
        }
    }
}