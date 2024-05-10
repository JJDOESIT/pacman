#include "points.h"

// Update the total amount of points
void Points::update(int n)
{
    n_points += n;
}

// Reset the total amount of points
void Points::reset()
{
    n_points = 0;
    n_coins = 0;
    n_initial_coins = 0;
    stringify();
}

// Turn the points number into a readable string
void Points::stringify()
{
    int total = n_points;
    int index = POINT_STRING_SIZE - 1;

    // If the total number of points is 0
    if (total == 0)
    {
        while (index)
        {
            points_array[index] = '0';
            index--;
        }
    }

    // While the total number of points is not 0
    while (total != 0)
    {
        // Find the last digit and place it in the array
        int last_digit = total % 10;
        points_array[index] = last_digit + 48;
        total = total / 10;
        index -= 1;
    }
    text.setString(points_array);
}

// Increament the total number of coins
void Points::increament_coins()
{
    n_coins++;
}

// Decreament the total number of coins
void Points::decreament_coins()
{
    n_coins--;
}

// Set the initial number of coins
void Points::set_n_initial_coins(int n)
{
    n_initial_coins = n;
}

// Return whether the player has got all the coins or not
bool Points::has_won()
{
    if (n_initial_coins == 0)
    {
        return false;
    }
    else
    {
        return (n_coins == 0);
    }
}

// Return the total number of points
int Points::get_n_points()
{
    return n_points;
}

// Return the total number of coins
int Points::get_n_coins()
{
    return n_coins;
}

// Return a pointer to the sf::Text reference
sf::Text *Points::get_text()
{
    return &text;
}

// Return a pointer to the sf::Font reference
sf::Font *Points::get_font()
{
    return &font;
}
