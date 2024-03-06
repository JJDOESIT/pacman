#include "SFML/Graphics.hpp"

#include <map>
#include <string>

#ifndef _TEXTURE_MANAGER_
#define _TEXTURE_MANAGER_

class Texture_Manager
{
private:
    std::map<std::string, sf::Texture> texture_map;

public:
    Texture_Manager();
    sf::Texture *get_texture(std::string key);
};

#endif