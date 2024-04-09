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

    int linear_directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int direction = best_direction(moves, occupant, target_x, target_y);

    static_cast<Ghost *>(occupant)->set_best_move(occupant->get_x_position() + linear_directions[direction][0], occupant->get_y_position() + linear_directions[direction][1]);
    occupant->set_direction(direction);
}

// Handle blinky's chase mode
void AI::blinky(Board *b, Navigation *n, Occupant *blinky, Occupant *pacman)
{
    bool *moves = n->get_possible_moves(blinky, b);

    // Set blinky's target tile to be pacman's position
    int target_x = static_cast<Pacman *>(pacman)->get_x_position();
    int target_y = static_cast<Pacman *>(pacman)->get_y_position();

    int linear_directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int direction = best_direction(moves, blinky, target_x, target_y);

    static_cast<Ghost *>(blinky)->set_best_move(blinky->get_x_position() + linear_directions[direction][0], blinky->get_y_position() + linear_directions[direction][1]);
    blinky->set_direction(direction);
}

// Handle pinky's chase mode
void AI::pinky(Board *b, Navigation *n, Occupant *pinky, Occupant *pacman)
{
    bool *moves = n->get_possible_moves(pinky, b);

    int target_x = static_cast<Pacman *>(pacman)->get_x_position();
    int target_y = static_cast<Pacman *>(pacman)->get_y_position();

    // Set pinky's target tile to be four spaces ahead of pacman
    int linear_directions_target[4][2] = {{-4, 0}, {0, 4}, {4, 0}, {0, -4}};
    int linear_directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    target_x += linear_directions_target[static_cast<Pacman *>(pacman)->get_direction()][0];
    target_y += linear_directions_target[static_cast<Pacman *>(pacman)->get_direction()][1];

    int direction = best_direction(moves, pinky, target_x, target_y);

    static_cast<Ghost *>(pinky)->set_best_move(pinky->get_x_position() + linear_directions[direction][0], pinky->get_y_position() + linear_directions[direction][1]);
    pinky->set_direction(direction);
}

// Handle inky's chase mode
void AI::inky(Board *b, Navigation *n, Occupant *inky, Occupant *blinky, Occupant *pacman)
{

    bool *moves = n->get_possible_moves(inky, b);

    int target_x = static_cast<Pacman *>(pacman)->get_x_position();
    int target_y = static_cast<Pacman *>(pacman)->get_y_position();

    // Find the space two ahead of pacman's current direction
    int linear_directions_target[4][2] = {{-2, 0}, {0, 2}, {2, 0}, {0, -2}};
    int linear_directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    target_x += linear_directions_target[static_cast<Pacman *>(pacman)->get_direction()][0];
    target_y += linear_directions_target[static_cast<Pacman *>(pacman)->get_direction()][1];

    // Calculate the x and y distances between the space two ahead of pacman
    // and blinky
    int x_distance = std::abs(blinky->get_x_position() - target_x);
    int y_distance = std::abs(blinky->get_y_position() - target_y);

    // Set inky to move towards the best route that will bring him closer to his target tile
    // (target tile is double the vector of x_distance and y_distance)
    int direction = best_direction(moves, inky, target_x + x_distance, target_y + y_distance);

    static_cast<Ghost *>(inky)->set_best_move(inky->get_x_position() + linear_directions[direction][0], inky->get_y_position() + linear_directions[direction][1]);
    inky->set_direction(direction);
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

// Calculate all ghosts AI patterns
void AI::all_ai(Board *b, Navigation *n, Occupant *pacman, Occupant *blinky, Occupant *pinky, Occupant *inky, Occupant *clyde)
{
    if (blinky && pacman)
    {
        AI::blinky(b, n, blinky, pacman);
    }
    if (pinky && pacman)
    {
        AI::pinky(b, n, pinky, pacman);
    }
    if (inky && blinky && pacman)
    {
        AI::inky(b, n, inky, blinky, pacman);
    }
    if (clyde && pacman)
    {
        AI::clyde(b, n, clyde, pacman);
    }
}

// Calculate all ghost's scatter patterns
void AI::scatter_all(Board *b, Navigation *n, Occupant *blinky, Occupant *pinky, Occupant *inky, Occupant *clyde)
{
    if (blinky)
    {
        scatter(b, n, blinky);
    }
    if (pinky)
    {
        scatter(b, n, pinky);
    }
    if (inky)
    {
        scatter(b, n, inky);
    }
    if (clyde)
    {
        scatter(b, n, clyde);
    }
}
