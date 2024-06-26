#include "board.h"
#include "navigation.h"
#include "occupant.h"
#include "ghost.h"
#include "linear_directions.h"
#include "state_manager.h"
#include "speed_manager.h"
#include "navigation.h"

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
    ~AI();
    void move_based_on_state(Draw_Manager *draw_manager, State_Manager *state_manager, Speed_Manager *speed_manager, int ghost, bool move = false);
    void move_all(Draw_Manager *draw_manager, State_Manager *state_manager, Speed_Manager *speed_manager);
    void set_target_tiles();
};

#endif