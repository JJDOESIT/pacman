#include "ai.h"

// Calculate the euclidean distance between two given points
int AI::euclidean_distance(int x1, int y1, int x2, int y2)
{
    return std::pow(std::abs(x1 - x2), 2) + std::pow(std::abs(y1 - y2), 2);
}

// Given an occupant, and a target tile, return the shortest direction (up, left, right, down)
// that will bring the occupant closer to the target tile
int AI::best_direction(bool moves[], Occupant *occupant, int target_x, int target_y)
{
    int linear_directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int tie_breaker[4] = {0, 4, 2, 1};
    int shortest_distance = -1;
    int shortest_direction = -1;

    for (int i = 0; i < 4; i++)
    {
        if (moves[i])
        {
            int x = occupant->get_x_position();
            int y = occupant->get_y_position();

            int d = euclidean_distance(x + linear_directions[i][0], y + linear_directions[i][1], target_x, target_y);

            // If the shortest direction hasn't been set yet (first iteration of the loop)
            if (shortest_direction == -1)
            {
                shortest_distance = d;
                shortest_direction = i;
            }
            // If a shorter path has been found
            else if (d < shortest_distance)
            {
                shortest_distance = d;
                shortest_direction = i;
            }
            // If two path's are the same distance, break the tie using order of precedence
            else if (d == shortest_distance)
            {
                if (tie_breaker[i] < tie_breaker[shortest_direction])
                {
                    shortest_direction = i;
                }
            }
        }
    }
    return shortest_direction;
}

// Handle the ghost's scatter behaivor
void AI::scatter(Board *b, Navigation *n, Occupant *occupant)
{
    bool *moves = n->get_possible_moves(occupant, b);
    int target_x = static_cast<Ghost *>(occupant)->get_target_x_tile();
    int target_y = static_cast<Ghost *>(occupant)->get_target_y_tile();
    n->move(occupant, b, best_direction(moves, occupant, target_x, target_y));
}

// Handle blinky's chase mode
void AI::blinky(Board *b, Navigation *n, Occupant *blinky, Occupant *pacman)
{
    bool *moves = n->get_possible_moves(blinky, b);

    // Set blinky's target tile to be pacman's position
    int target_x = static_cast<Pacman *>(pacman)->get_x_position();
    int target_y = static_cast<Pacman *>(pacman)->get_y_position();

    n->move(blinky, b, best_direction(moves, blinky, target_x, target_y));
}

// Handle pinky's chase mode
void AI::pinky(Board *b, Navigation *n, Occupant *pinky, Occupant *pacman)
{
    bool *moves = n->get_possible_moves(pinky, b);

    int target_x = static_cast<Pacman *>(pacman)->get_x_position();
    int target_y = static_cast<Pacman *>(pacman)->get_y_position();

    // Set pinky's target tile to be four spaces ahead of pacman
    int direction = static_cast<Pacman *>(pacman)->get_direction();
    int linear_directions[4][2] = {{-4, 0}, {0, 4}, {4, 0}, {0, -4}};
    target_x += linear_directions[direction][0];
    target_y += linear_directions[direction][1];

    n->move(pinky, b, best_direction(moves, pinky, target_x, target_y));
}

// Handle inky's chase mode
void AI::inky(Board *b, Navigation *n, Occupant *inky, Occupant *blinky, Occupant *pacman)
{

    bool *moves = n->get_possible_moves(inky, b);

    int target_x = static_cast<Pacman *>(pacman)->get_x_position();
    int target_y = static_cast<Pacman *>(pacman)->get_y_position();

    // Find the space two ahead of pacman's current direction
    int direction = static_cast<Pacman *>(pacman)->get_direction();
    int linear_directions[4][2] = {{-2, 0}, {0, 2}, {2, 0}, {0, -2}};
    target_x += linear_directions[direction][0];
    target_y += linear_directions[direction][1];

    // Calculate the x and y distances between the space two ahead of pacman
    // and blinky
    int x_distance = std::abs(blinky->get_x_position() - target_x);
    int y_distance = std::abs(blinky->get_y_position() - target_y);

    // Set inky to move towards the best route that will bring him closer to his target tile
    // (target tile is double the vector of x_distance and y_distance)
    n->move(inky, b, best_direction(moves, inky, target_x + x_distance, target_y + y_distance));
}

// Handle clyde's chase mode
void AI::clyde(Board *b, Navigation *n, Occupant *clyde, Occupant *pacman)
{
    bool *moves = n->get_possible_moves(clyde, b);

    int target_x = static_cast<Pacman *>(pacman)->get_x_position();
    int target_y = static_cast<Pacman *>(pacman)->get_y_position();

    int distance = euclidean_distance(clyde->get_x_position(), clyde->get_y_position(), target_x, target_y);

    // If clyde is within 8 tiles of pacman, he will scatter to his tile
    // else he will target pacman's current position (exactly the same as blinky)
    if (distance <= 64)
    {
        scatter(b, n, clyde);
    }
    else
    {
        blinky(b, n, clyde, pacman);
    }
}
