#ifndef RENDER_ELEMENT_H
#define RENDER_ELEMENT_H

#include "../DataStructures/Structs.h"
#include "../DataStructures/Vector2.h"
#include <SFML/Graphics.hpp>
#include <string>

// base class for render elements, other elements such a sprite, text ect.. need
// to inherit from this
class RenderElement
{
 public:
  // Interface for inhereted classes. 
  virtual bool checkOnscreen(sf::RenderTexture& render_texture) = 0;
  virtual void ConvertToScreenSpaceByCamera(
    Structs::Rect camera_viewbox, Structs::XY camera_resolution,
    Structs::XY display_resolution)                    = 0;
  virtual void draw(sf::RenderTexture& render_texture) = 0;

  // pre-written functions for all classes inheriting from this:
  //
  // various getter and setter functions for variables.
  int getLayer();
  void setLayer(int new_layer);

  float getScale();
  void setScale(float new_scale);

  Structs::XY getPosition();
  void setPosition(float new_x, float new_y);
  void modifyPosition(float new_x, float new_y);

  Vector2* getVector();
  void setVector(float new_x, float new_y);
  void moveByVector(float dt);

  float getVectorSpeed();
  void setVectorSpeed(float new_speed);
  void modifyVectorSpeed(float value);

  bool getMoveWithCamera();
  void setMoveWithCamera(bool new_state);

  float getMovePercentage();
  void setMovePercentage(float new_move_percentage);

 private:
  float scale = 1;
  int layer   = 1;
  Structs::XY position;
  Vector2 vector;
  float vector_speed     = 100;
  bool moves_with_camera = 0;
  float move_percentage  = 1;
};

// render element for sprites.
class SpriteRenderElement : public RenderElement
{
 public:
  // constructors. allow setting up with a sprite and layer.
  SpriteRenderElement();
  SpriteRenderElement(std::string file_path);
  SpriteRenderElement(std::string file_path, int layer);

  // functions that all renderElements must have, implemented from above class.
  bool checkOnscreen(sf::RenderTexture& render_texture);
  void ConvertToScreenSpaceByCamera(
    Structs::Rect camera_viewbox, Structs::XY camera_resolution,
    Structs::XY display_resolution);
  void draw(sf::RenderTexture& texture);

  // sprite specific functions:
  sf::Sprite* getSprite();
  bool setUpSpriteFromPath(std::string file_path);
  Structs::XY getSpriteCenter();

 private:
  // sprite specific variables
  sf::Sprite sprite;
  sf::Texture texture;
};

#endif // !RENDER_ELEMENT_H
