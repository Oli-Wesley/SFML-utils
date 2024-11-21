#include "SpriteUtils.h"
#include <iostream>

// returns a sprite with a texture based on a given path
sf::Sprite SpriteUtils::getSpriteFromPath(std::string path, sf::Texture &texture)
{
  sf::Sprite sprite;
  if (texture.loadFromFile(path))
  {
    sprite.setTexture(texture);
    return sprite;
  }
  std::cout << "Failed to load Texture from path " << path;
  return sprite;
}

sf::Sprite
SpriteUtils::getSpriteFromPath(std::string path, sf::Texture& texture, int scale)
{
  sf::Sprite sprite;
  if (texture.loadFromFile(path))
  {
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
    return sprite;
  }
  std::cout << "Failed to load Texture from path " << path << "\n";
  return sprite;
}
