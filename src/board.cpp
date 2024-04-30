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

void Board::print_board()
{
    for (int row = 0; row < nRows; row++)
    {
        for (int col = 0; col < nCols; col++)
        {
            if (board[row][col].find_occupant(type::PLAYER))
            {
                std::cout << "p";
            }
            else if (board[row][col].find_occupant(type::GHOST))
            {
                std::cout << "g";
            }
            else if (board[row][col].find_occupant(type::COIN))
            {
                std::cout << "c";
            }
            else if (board[row][col].find_occupant(type::WALL))
            {
                std::cout << "x";
            }
        }
        std::cout << '\n';
    }
}

// Return a pointer to the board
std::vector<std::vector<Occupant_List>> *Board::get_board()
{
    return &board;
}

// Delete the board
void Board::clear()
{
    for (int row = 0; row < nRows; row++)
    {
        for (int col = 0; col < nCols; col++)
        {
            board[row][col].clear();
        }
    }
    board.clear();

    nRows = 0;
    nCols = 0;
}