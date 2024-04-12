#include "board.h"
#include "navigation.h"
#include "occupant.h"
#include "ghost.h"
#include "linear_directions.h"
#include "state_manager.h"
#include "ghost_clocks.h"

#include <cmath>

#ifndef _AI_
#define _AI_

class AI
{
private:
    Board *b;
    Navigation *n;
    Occupant *characters[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};

    int euclidean_distance(int x1, int y1, int x2, int y2);
    int best_direction(bool moves[], Occupant *occupant, int target_x, int target_y);
    void scatter(int ghost);
    void blinky_ai(int ghost);
    void pinky_ai(int ghost);
    void inky_ai(int ghost);
    void clyde_ai(int ghost);
    void run(int ghost);
    void move_in_current_direction(int ghost);
    void move_to_escape_tile(State_Manager *state_manager, int ghost);

    void return_to_start(State_Manager *state_manager, int ghost);

public:
    AI(Board *b, Navigation *n, Occupant *characters[5]);
    void move_based_on_state(State_Manager *state_manager, Ghost_Clocks *ghost_clocks, int ghost);
    void move_all(State_Manager *state_manager, Ghost_Clocks *ghost_clocks);
};

#endif