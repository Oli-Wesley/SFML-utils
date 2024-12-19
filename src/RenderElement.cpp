#include "RenderElement.h"
#include "Vector2.h"
#include <iostream>

int RenderElement::getLayer()
{
  return layer;
}

void RenderElement::setLayer(int new_layer)
{
  layer = new_layer;
}

float RenderElement::getScale()
{
  return scale;
}

void RenderElement::setScale(float new_scale)
{
  scale = new_scale;
}

RenderElement::XY RenderElement::getPosition()
{
  return position;
}

void RenderElement::setPosition(float new_x, float new_y)
{
  position.x = new_x;
  position.y = new_y;
}

void RenderElement::modifyPosition(float new_x, float new_y)
{
  position.x += new_x;
  position.y += new_y;
}

Vector2* RenderElement::getVector()
{
  return &vector;
}

void RenderElement::setVector(float new_x, float new_y)
{
  vector.x = new_x;
  vector.y = new_y;
  vector.normalise();
}

void RenderElement::moveByVector(float dt)
{
  position.x += vector.x * dt * vector_speed;
  position.y += vector.y * dt * vector_speed;
}

float RenderElement::getVectorSpeed()
{
  return vector_speed;
}

void RenderElement::setVectorSpeed(float new_speed)
{
  vector_speed = new_speed;
}

void RenderElement::modifyVectorSpeed(float value)
{
  vector_speed += value;
}

bool RenderElement::getMoveWithCamera()
{
  return moves_with_camera;
}

void RenderElement::setMoveWithCamera(bool new_state)
{
  moves_with_camera = new_state;
}

float RenderElement::getMovePercentage()
{
  return move_percentage;
}

void RenderElement::setMovePercentage(float new_move_percentage)
{
  if (move_percentage > -1 && move_percentage < 1)
  {
    move_percentage = new_move_percentage;
  }
  else if (move_percentage > -100 && move_percentage < 100)
  {
    move_percentage = new_move_percentage / 100;
  }
  else
  {
    std::cout << "ERROR: Invalid Move Percentage";
    throw;
  }
}

void RenderElement::setMovePercentage(int new_move_percentage)
{
  if (move_percentage > -100 && move_percentage < 100)
  {
    move_percentage = new_move_percentage / 100;
  }
  else
  {
    std::cout << "ERROR: Invalid Move Percentage";
    throw;
  }
}

// init class without a file path
SpriteRenderElement::SpriteRenderElement()
{
  setMoveWithCamera(0);
  setMovePercentage(1);
  setLayer(100);
}

// init class with a file path
SpriteRenderElement::SpriteRenderElement(std::string file_path)
{
  setMoveWithCamera(0);
  setMovePercentage(1);
  setLayer(100);
  setUpSpriteFromPath(file_path);
}

SpriteRenderElement::SpriteRenderElement(std::string file_path, int layer)
{
  setMoveWithCamera(0);
  setMovePercentage(1);
  setLayer(layer);
  setUpSpriteFromPath(file_path);
}

// checks if the sprite is on screen, given a texture and its current bounds.
bool SpriteRenderElement::checkOnscreen(sf::RenderTexture& display)
{
  // store sprite bound rect
  sf::FloatRect sprite_bounds = sprite.getGlobalBounds();

  // left
  if (sprite_bounds.left + sprite_bounds.width < 0)
    return 0;
  // right
  else if (sprite_bounds.left > display.getSize().x)
    return 0;
  // top
  else if (sprite_bounds.top + sprite_bounds.height < 0)
    return 0;
  // bottom
  else if (sprite_bounds.top > display.getSize().y)
    return 0;
  return 1;
}

// convert from world space to screenspace position
void SpriteRenderElement::ConvertToScreenSpaceByCamera(
  float camera_x, float camera_y, float camera_center_x, float camera_center_y,
  float x_factor, float y_factor, float camera_zoom)
{
  // convert pos
  XY new_pos;

  // apply position based on camera zoom:
  float pos_x          = getPosition().x / x_factor;
  float pos_y          = getPosition().y / y_factor;
  float center_x       = camera_center_x / x_factor;
  float center_y       = camera_center_y / y_factor;
  float scale_factor_x = getScale() * camera_zoom / x_factor;
  float scale_factor_y = getScale() * camera_zoom / y_factor;

  // this does not work if the camera's resolution the window resolution and the zoom is anything but 1. 
  new_pos.x = (pos_x - center_x) * camera_zoom / x_factor + center_x;
  new_pos.y = (pos_y - center_y) * camera_zoom / x_factor + center_y;

  XY old_center = getSpriteCenter();

  // convert scale.
  sprite.setScale(scale_factor_x, scale_factor_y);

  XY new_center = getSpriteCenter();

  new_pos.x += old_center.x - new_center.x;
  new_pos.y += old_center.y - old_center.y;

  sprite.setPosition(new_pos.x, new_pos.y);
}

// returns a reference to the sprite.
sf::Sprite* SpriteRenderElement::getSprite()
{
  return &sprite;
}

bool SpriteRenderElement::setUpSpriteFromPath(std::string file_path)
{
  if (texture.loadFromFile(file_path))
  {
    sprite.setTexture(texture);
    return true;
  }
  return false;
}

RenderElement::XY SpriteRenderElement::getSpriteCenter()
{
  XY center_coords;
  sf::Rect sprite_bounds = sprite.getGlobalBounds();

  center_coords.x = sprite_bounds.left + sprite_bounds.width / 2;
  center_coords.y = sprite_bounds.top + sprite_bounds.height / 2;
  return center_coords;
}
