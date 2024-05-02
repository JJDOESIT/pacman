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

        for (int c = 0; c < line.length(); c++)
        {
            if (line[c] == '=')
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
        index_found = false;

        if (key == "SCREEN_WIDTH")
        {
            SCREEN_WIDTH = std::stoi(value);
        }
        else if (key == "BODY_HEIGHT")
        {
            BODY_HEIGHT = std::stoi(value);
        }
        else if (key == "HEADER_HEIGHT")
        {
            HEADER_HEIGHT = std::stoi(value);
        }
        else if (key == "FOOTER_HEIGHT")
        {
            FOOTER_HEIGHT = std::stoi(value);
        }
        else if (key == "N_PACMAN_LIVES")
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
        else if (key == "BORDER_OUTLINE_THICKNESS")
        {
            BORDER_OUTLINE_THICKNESS = std::stoi(value);
        }
        else if (key == "MAP_DIR")
        {
            MAP_DIR = value;
        }
        else if (key == "JSON_DIR")
        {
            JSON_DIR = value;
        }

        key.clear();
        value.clear();
    }

    ifstream.close();
}
