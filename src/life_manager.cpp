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

// Reset lives
void Life_Manager::reset()
{
    n_pacman_lives = Config::N_PACMAN_LIVES;
    collision = false;
}
