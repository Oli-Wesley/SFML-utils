#include "RenderElement.h"
#include "../DataStructures/Structs.h"
#include "../DataStructures/Vector2.h"
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

Structs::XY RenderElement::getPosition()
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
  if (move_percentage >= -1 && move_percentage <= 1)
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

void SpriteRenderElement::ConvertToScreenSpaceByCamera(
  Structs::Rect camera_viewbox, Structs::XY camera_resolution,
  Structs::XY display_resolution)
{
  // assign variables
  Structs::XY screen_to_display_factor;
  Structs::XY view_to_camera_factor;
  Structs::Rect sprite_bounds;
  Structs::XY camera_center;

  screen_to_display_factor.x = display_resolution.x / camera_resolution.x;
  screen_to_display_factor.y = display_resolution.y / camera_resolution.y;

  view_to_camera_factor.x = camera_viewbox.width / camera_resolution.x;
  view_to_camera_factor.y = camera_viewbox.height / camera_resolution.y;

  sprite_bounds.x      = sprite.getLocalBounds().left;
  sprite_bounds.y      = sprite.getLocalBounds().top;
  sprite_bounds.width  = sprite.getLocalBounds().width;
  sprite_bounds.height = sprite.getLocalBounds().height;

  camera_center.x = camera_viewbox.x + camera_viewbox.width / 2;
  camera_center.y = camera_viewbox.y + camera_viewbox.height / 2;

  // Position and Scale
  Structs::XY sprite_pos;
  Structs::XY new_scale;

  // get scaling
  new_scale.x = getScale() / view_to_camera_factor.x;
  new_scale.y = getScale() / view_to_camera_factor.y;

  // get position of sprite
  sprite_pos.x = getPosition().x + camera_center.x;
  sprite_pos.y = getPosition().y + camera_center.y;

  // apply movement percentage
  sprite_pos.x -= (getMovePercentage() * camera_center.x) - camera_viewbox.width/2;
  sprite_pos.y -= (getMovePercentage() * camera_center.y) - camera_viewbox.height/2;

  
  // move position into screenspace
  sprite_pos.x -= camera_center.x;
  sprite_pos.y -= camera_center.y;

  // scale based on zoom
  sprite_pos.x /= view_to_camera_factor.x;
  sprite_pos.y /= view_to_camera_factor.y;

  // apply scale and position
  sprite.setScale(new_scale.x, new_scale.y);
  sprite.setPosition(sprite_pos.x, sprite_pos.y);
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

Structs::XY SpriteRenderElement::getSpriteCenter()
{
  Structs::XY center_coords;
  sf::Rect sprite_bounds = sprite.getGlobalBounds();

  center_coords.x = sprite_bounds.left + sprite_bounds.width / 2;
  center_coords.y = sprite_bounds.top + sprite_bounds.height / 2;
  return center_coords;
}
