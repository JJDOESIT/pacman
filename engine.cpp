#include "engine.h"

Engine::Engine(std::string map_name)
{
    std::ifstream infile;

    infile.open(map_name);

    // If the file cannot be found
    if (!infile)
    {
        std::cout << "Map file not found ..." << std::endl;
        exit(1);
    }

    std::string row;
    int current_row = 0;
    int current_col = 0;
    std::vector<Occupant_List> row_vector;

    // Parse the map line by line
    while (std::getline(infile, row, '/'))
    {
        // trcc represents top right corner connector wall
        if (row == "trcc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPRIGHTCORNERCONNECTOR)));
        }
        // tlcc represents top left corner connector wall
        if (row == "tlcc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPLEFTCORNERCONNECTOR)));
        }
        // tlc represents top left corner wall
        if (row == "tlcd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPLEFTCORNERDOUBLE)));
        }
        // trc represents top right corner wall
        if (row == "trcd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPRIGHTCORNERDOUBLE)));
        }
        // brc represents bottom right corner wall
        if (row == "brcd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMRIGHTCORNERDOUBLE)));
        }
        // blc represents bottom left corner wall
        if (row == "blcd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMLEFTCORNERDOUBLE)));
        }
        // tlcs represents top left single corner wall
        if (row == "tlcs")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPLEFTCORNERSINGLE)));
        }
        // trc represents top right single corner wall
        if (row == "trcs")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPRIGHTCORNERSINGLE)));
        }
        // brcs represents bottom right single corner wall
        if (row == "brcs")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMRIGHTCORNERSINGLE)));
        }
        // blcs represents bottom left single corner wall
        if (row == "blcs")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMLEFTCORNERSINGLE)));
        }
        // trcsc represents top right corner single connector wall
        if (row == "trcsc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPRIGHTCORNERSINGLECONNECTOR)));
        }
        // tlcsc represents top left corner single connector wall
        if (row == "tlcsc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::TOPLEFTCORNERSINGLECONNECTOR)));
        }
        // blcsc represents bottom left corner single connector wall
        if (row == "blcsc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMLEFTCORNERSINGLECONNECTOR)));
        }
        // brcsc represents bottom right corner single connector wall
        if (row == "brcsc")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::BOTTOMRIGHTCORNERSINGLECONNECTOR)));
        }
        // svl represents straight vertical left double wall
        if (row == "svld")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTVERTICALLEFTDOUBLE)));
        }
        // svr represents straight vertical right doub;e wall
        if (row == "svrd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTVERTICALRIGHTDOUBLE)));
        }
        // svml represents straight vertical middle left wall
        if (row == "svml")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTVERTICALMIDDLELEFT)));
        }
        // svmr represents straight vertical middle right wall
        if (row == "svmr")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTVERTICALMIDDLERIGHT)));
        }
        // sht represents straight horizontal top double wall
        if (row == "shtd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTHORIZONTALTOPDOUBLE)));
        }
        // shb represents straight horizontal bottom double wall
        if (row == "shbd")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTHORIZONTALBOTTOMDOUBLE)));
        }
        // shts represents straight horizontal top single wall
        if (row == "shts")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTHORIZONTALTOPSINGLE)));
        }
        // shbs represents straight horizontal bottom single wall
        if (row == "shbs")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::STRAIGHTHORIZONTALBOTTOMSINGLE)));
        }
        // f represents a filled in wall
        if (row == "f")
        {
            row_vector.push_back(Occupant_List(new Wall(current_row, current_col, wall_type::FILLED)));
        }
        // c represents a coin
        else if (row == "c")
        {
            row_vector.push_back(Occupant_List(new Coin(current_row, current_col)));
        }
        // s represents an empty space (just a coin toggled off to save space)
        else if (row == "s")
        {
            row_vector.push_back(Occupant_List(new Coin(current_row, current_col, false)));
        }
        // p represents pacman
        else if (row == "p")
        {
            row_vector.push_back(Occupant_List(new Coin(current_row, current_col, false)));
            pacman = new Pacman(current_row, current_col);
            row_vector[current_col].push(pacman);
        }
        // n represents a new line
        else if (row == "n")
        {
            current_row++;
            current_col = -1;
            (*board.get_board()).push_back(row_vector);
            row_vector.clear();
            infile.ignore();
        }
        // e represents the end of the map file
        else if (row == "e")
        {
            board.set_rows(current_row + 1);
            board.set_cols(current_col);
            (*board.get_board()).push_back(row_vector);
        }
        current_col++;
    }
}

// Return a pointer to pacman
Occupant *Engine::get_pacman()
{
    return pacman;
}

// Return a pointer to the board instance
Board *Engine::get_board()
{
    return &board;
}

// Return a pointer to the navigation instance
Navigation *Engine::get_navigation()
{
    return &navigation;
}
