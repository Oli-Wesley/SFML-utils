#include <SFML/Graphics.hpp>
#include <string>

namespace SpriteUtils
{
  sf::Sprite getSpriteFromPath(std::string path);
  sf::Sprite getSpriteFromPath(std::string path, int scale);
}