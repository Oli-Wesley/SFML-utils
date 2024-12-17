#ifndef SPRITE_UTILS_H
#define SPRITE_UTILS_H

#include <SFML/Graphics.hpp>
#include <string>

namespace SpriteUtils
{
  sf::Sprite getSpriteFromPath(std::string path, sf::Texture& texture);
  sf::Sprite
  getSpriteFromPath(std::string path, sf::Texture& texture, float scale);

  sf::Font getFontFromPath(std::string path);

  sf::Text setupText(
    sf::Font& font, std::string string, int character_size, sf::Color color,
    int x_pos, int y_pos);

  sf::Text setupText(
    sf::Font& font, std::string string, int character_size, sf::Color color);
}

#endif