#ifndef _CONFIG_
#define _CONFIG_

#include "enum.h"
#include <string>

class Config
{
public:
    static inline int SCREEN_WIDTH = 560;
    static inline int BODY_HEIGHT = 620;
    static inline int HEADER_HEIGHT = 100;
    static inline int FOOTER_HEIGHT = 100;
    static inline int N_PACMAN_LIVES = 3;

    static inline int DEFAULT_PACMAN_DIRECTION = moves::UP;

    static inline int DEFAULT_BLINKY_DIRECTION = moves::RIGHT;
    static inline int DEFAULT_PINKY_DIRECTION = moves::LEFT;
    static inline int DEFAULT_INKY_DIRECTION = moves::RIGHT;
    static inline int DEFAULT_CLYDE_DIRECTION = moves::LEFT;

    static inline int BLINKY_ESCAPE_TILE[2] = {12, 14};
    static inline int PINKY_ESCAPE_TILE[2] = {12, 14};
    static inline int INKY_ESCAPE_TILE[2] = {12, 13};
    static inline int CLYDE_ESCAPE_TILE[2] = {12, 14};

    static inline int SCATTER_TIME = 7000;
    static inline int CHASE_TIME = 20000;
    static inline int DISABLE_TIME = 5000;

    static inline int PACMAN_SPEED = 200;
    static inline int GHOST_SPEED = 300;
    static inline int FRIGHTENED_GHOST_SPEED = 400;

    static inline int BORDER_OUTLINE_THICKNESS = 1;

    static inline std::string MAP_DIR = "maps/";
    static inline std::string JSON_DIR = "json/";
};

#endif