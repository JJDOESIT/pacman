#include "life_manager.h"

Life_Manager::Life_Manager(int n_lives)
{
    n_pacman_lives = n_lives;
}

// Decrease the player's lives by one
void Life_Manager::decrement()
{
    n_pacman_lives -= 1;
}

// Set if a collision has happened
void Life_Manager::set_collision(bool c)
{
    collision = c;
}

// Return whether a collision has happened or not
bool Life_Manager::get_collision()
{
    return collision;
}

// Return the number of pacman lives
int Life_Manager::get_n_lives()
{
    return n_pacman_lives;
}

// Set the number of pacman lives
void Life_Manager::set_n_lives(int n)
{
    n_pacman_lives = n;
}

bool Life_Manager::is_game_over()
{
    return n_pacman_lives == 0;
}

// Reset lives
void Life_Manager::reset()
{
    n_pacman_lives = Config::N_PACMAN_LIVES;
    collision = false;
}
