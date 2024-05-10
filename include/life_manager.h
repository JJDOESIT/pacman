#ifndef _LIFE_MANAGER_
#define _LIFE_MANAGER_

#include "config.h"
#include <string>

class Life_Manager
{
private:
    int n_pacman_lives;
    bool collision = false;

public:
    Life_Manager(int n_lives);
    void decrement();
    void set_collision(bool c);
    bool get_collision();
    int get_n_lives();
    void set_n_lives(int n);
    bool is_game_over();
    void reset();
};

#endif