#include <SFML/Graphics.hpp>
#include <string>

namespace SpriteUtils
{
  sf::Sprite getSpriteFromPath(std::string path, sf::Texture &texture);
  sf::Sprite
  getSpriteFromPath(std::string path, sf::Texture &texture, int scale);
}