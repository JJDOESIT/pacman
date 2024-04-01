#include "board.h"
#include "navigation.h"
#include "occupant.h"
#include "ghost.h"

#include <cmath>

#ifndef _AI_
#define _AI_

class AI
{
public:
    int euclidean_distance(int x1, int y1, int x2, int y2);
    int best_direction(bool moves[], Occupant *occupant, int target_x, int target_y);
    void scatter(Board *b, Navigation *n, Occupant *occupant);
    void blinky(Board *b, Navigation *n, Occupant *blinky, Occupant *pacman);
    void pinky(Board *b, Navigation *n, Occupant *pinky, Occupant *pacman);
    void inky(Board *b, Navigation *n, Occupant *inky, Occupant *blinky, Occupant *pacman);
    void clyde(Board *b, Navigation *n, Occupant *clyde, Occupant *pacman);
};

#endif