#include "SpriteUtils.h"
#include <iostream>

// returns a sprite with a texture based on a given path
sf::Sprite
SpriteUtils::getSpriteFromPath(std::string path, sf::Texture& texture)
{
  sf::Sprite sprite;
  if (texture.loadFromFile(path))
  {
    sprite.setTexture(texture);
    return sprite;
  }
  std::cout << "Failed to load Texture from path " << path << "\n";
  return sprite;
}

sf::Sprite SpriteUtils::getSpriteFromPath(
  std::string path, sf::Texture& texture, float scale)
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

sf::Font SpriteUtils::getFontFromPath(std::string path)
{
  sf::Font temp_font;
  if (!temp_font.loadFromFile(path))
  {
    std::cout << "Failed to load Font from path " << path << "\n";
  }
  return temp_font;
}

sf::Text SpriteUtils::setupText(
  sf::Font& font, std::string string, int character_size, sf::Color color,
  int x_pos, int y_pos)
{
  sf::Text temp_text;
  temp_text.setFont(font);
  temp_text.setString(string);
  temp_text.setCharacterSize(character_size);
  temp_text.setColor(color);
  temp_text.setPosition(x_pos, y_pos);

  return temp_text;
}

sf::Text SpriteUtils::setupText(
  sf::Font& font, std::string string, int character_size, sf::Color color)
{
  sf::Text temp_text;
  temp_text.setFont(font);
  temp_text.setString(string);
  temp_text.setCharacterSize(character_size);
  temp_text.setColor(color);

  return temp_text;
}
