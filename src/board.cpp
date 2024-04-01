#include "board.h"

// Return number of rows in the board
int Board::get_rows()
{
    return nRows;
}

// Return number of columns in the board
int Board::get_cols()
{
    return nCols;
}

// Set the number of rows
void Board::set_rows(int n)
{
    nRows = n;
}

// Set the number of columns
void Board::set_cols(int n)
{
    nCols = n;
}

// Return a pointer to the board
std::vector<std::vector<Occupant_List>> *Board::get_board()
{
    return &board;
}

// Print the board state
void Board::print_board()
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            if (board[i][j].find_occupant(type::PLAYER) != nullptr)
            {
                std::cout << 'p';
            }
            else if (board[i][j].find_occupant(type::GHOST) != nullptr)
            {
                std::cout << 'g';
            }
            else if (board[i][j].find_occupant(type::WALL) != nullptr)
            {
                std::cout << 'x';
            }
            else if (board[i][j].find_occupant(type::COIN) != nullptr)
            {
                if (static_cast<Coin *>(board[i][j].find_occupant(type::COIN))->get_toggled())
                {
                    std::cout << 'c';
                }
                else
                {
                    std::cout << 's';
                }
            }
        }
        std::cout << '\n';
    }
}