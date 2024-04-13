#include "occupant_list.h"
#include "coin.h"

#ifndef _BOARD_
#define _BOARD_

class Board
{
private:
    std::vector<std::vector<Occupant_List>> board;
    int nRows = 0;
    int nCols = 0;

public:
    std::vector<std::vector<Occupant_List>> *get_board();
    void clear();
    int get_rows();
    int get_cols();
    void set_rows(int n);
    void set_cols(int n);
    void print_board();
};

#endif