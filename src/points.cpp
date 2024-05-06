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
