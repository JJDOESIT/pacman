#include "config.h"

void Config::read(std::string config_path)
{
    std::ifstream ifstream;

    ifstream.open(config_path);

    // Check if the file was created
    if (!ifstream)
    {
        std::cout << "Error: Cannot open file ..." << std::endl;
        exit(1);
    }

    std::string line, key, value;
    bool index_found = false;
    while (!ifstream.eof())
    {
        std::getline(ifstream, line);

        scan(line, key, value, '=');

        if (key == "N_PACMAN_LIVES")
        {
            N_PACMAN_LIVES = std::stoi(value);
        }
        else if (key == "DEFAULT_PACMAN_DIRECTION")
        {
            DEFAULT_PACMAN_DIRECTION = std::stoi(value);
        }
        else if (key == "DEFAULT_BLINKY_DIRECTION")
        {
            DEFAULT_BLINKY_DIRECTION = std::stoi(value);
        }
        else if (key == "DEFAULT_PINKY_DIRECTION")
        {
            DEFAULT_PINKY_DIRECTION = std::stoi(value);
        }
        else if (key == "DEFAULT_INKY_DIRECTION")
        {
            DEFAULT_INKY_DIRECTION = std::stoi(value);
        }
        else if (key == "DEFAULT_CLYDE_DIRECTION")
        {
            DEFAULT_CLYDE_DIRECTION = std::stoi(value);
        }
        else if (key == "SCATTER_TIME")
        {
            SCATTER_TIME = std::stoi(value);
        }
        else if (key == "DISABLE_TIME")
        {
            DISABLE_TIME = std::stoi(value);
        }
        else if (key == "FRIGHTENED_TIME")
        {
            FRIGHTENED_TIME = std::stoi(value);
        }
        else if (key == "PACMAN_SPEED")
        {
            PACMAN_SPEED = std::stoi(value);
        }
        else if (key == "GHOST_SPEED")
        {
            GHOST_SPEED = std::stoi(value);
        }
        else if (key == "FRIGHTENED_GHOST_SPEED")
        {
            FRIGHTENED_GHOST_SPEED = std::stoi(value);
        }
        else if (key == "BLINKY_ESCAPE_TILE")
        {
            std::string x, y;
            scan(value, x, y, ',');
            BLINKY_ESCAPE_TILE[0] = std::stoi(x);
            BLINKY_ESCAPE_TILE[1] = std::stoi(y);
        }
    }
    ifstream.close();
}

// Parse a line to split it into key and value pair
void Config::scan(std::string line, std::string &key, std::string &value, char delimiter)
{
    key.clear();
    value.clear();

    bool index_found = false;

    for (int c = 0; c < line.length(); c++)
    {
        if (line[c] == delimiter)
        {
            index_found = true;
        }
        else if (index_found)
        {
            value += line[c];
        }
        else
        {
            key += line[c];
        }
    }
}
