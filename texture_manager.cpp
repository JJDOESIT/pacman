#include "texture_manager.h"

Texture_Manager::Texture_Manager()
{
    sf::Texture texture;

    // Top right corner connector wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(99, 45, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("trcc", texture));

    // Top left corner connector wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(90, 45, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("tlcc", texture));

    // Top left corner double wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(9, 27, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("tlcd", texture));

    // Top right corner double wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(0, 27, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("trcd", texture));

    // Bottom right corner double wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(36, 27, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("brcd", texture));

    // Bottom left corner double wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(45, 27, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("blcd", texture));

    // Top left single corner wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(18, 45, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("tlcs", texture));

    // Top right single corner wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(27, 45, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("trcs", texture));

    // Bottom right single corner wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(45, 45, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("brcs", texture));

    // Bottom left corner single wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(36, 45, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("blcs", texture));

     // Top left corner single connector wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(63, 36, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("tlcsc", texture));

    // Top right corner single connector wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(54, 36, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("trcsc", texture));

    // Bottom right corner single connector wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(90, 36, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("brcsc", texture));

    // Bottom left corner single connector wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(99, 36, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("blcsc", texture));

    // Straight horizontal top double wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(90, 27, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("shtd", texture));

    // Straight horizontal bottom double wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(108, 27, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("shbd", texture));

    // Straight horizontal top single wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(36, 36, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("shts", texture));

    // Straight horizontal bottom single wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(126, 27, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("shbs", texture));

    // Straight vertical left double wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(27, 27, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("svld", texture));

    // Straight vertical right double wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(18, 27, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("svrd", texture));

    // Straight vertical middle left wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(72, 36, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("svml", texture));

    // Straight vertical middle right wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(81, 36, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("svmr", texture));

    // Toggled coin
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(117, 45, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("c", texture));

    // Filled wall
    texture.loadFromFile("images/wall_sprite_sheet.png", sf::IntRect(108, 18, 8, 8));
    texture_map.insert(std::pair<std::string, sf::Texture>("f", texture));

    // Fully open mouth pacman
    texture.loadFromFile("images/general_sprite_sheet.png", sf::IntRect(0, 0, 16, 16));
    texture_map.insert(std::pair<std::string, sf::Texture>("fopm", texture));
}

// Return a pointer to the stored texture in the map
sf::Texture *Texture_Manager::get_texture(std::string key)
{
    return &texture_map[key];
}