#ifndef SPRITE_UTILS_H
#define SPRITE_UTILS_H

#include <SFML/Graphics.hpp>
#include <string>

namespace SpriteUtils
{
  sf::Sprite getSpriteFromPath(std::string path, sf::Texture &texture);
  sf::Sprite
  getSpriteFromPath(std::string path, sf::Texture &texture, int scale);
}

#endif