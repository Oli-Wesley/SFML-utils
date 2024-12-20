#ifndef RENDER_ELEMENT_H
#define RENDER_ELEMENT_H

#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include <string>

class RenderElement
{
 public:
  struct XY
  {
    float x = 0;
    float y = 0;
  };

  // functions that everything inheriting from need to impliment themselves
  // bool checkOnscreen(sf::Window window);
  // void moveByCamera(float camera_x, float camera_y);

  // pre-written functions for all classes inheriting from this
  // gettter and setter for layer value
  int getLayer();
  void setLayer(int new_layer);

  // getter and setter for scale value
  float getScale();
  void setScale(float new_scale);

  // getter setter, and modify for position;
  XY getPosition();
  void setPosition(float new_x, float new_y);
  void modifyPosition(float new_x, float new_y);

  // getter, setter and move by for vector;
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
  void setMovePercentage(int new_move_percentage);

 private:
  float scale = 1;
  int layer   = 1;
  XY position;
  Vector2 vector;
  float vector_speed     = 100;
  bool moves_with_camera = 0;
  float move_percentage  = 1;
};

class SpriteRenderElement : public RenderElement
{
 public:
  SpriteRenderElement();
  SpriteRenderElement(std::string file_path);
  SpriteRenderElement(std::string file_path, int layer);
  bool checkOnscreen(sf::RenderTexture& window);
  void ConvertToScreenSpaceByCamera(
    float camera_x, float camera_y, float camera_center_x,
    float camera_center_y, int camera_resolution_x, int camera_resolution_y, int display_resolution_x, int display_resolution_y,
    float camera_zoom);
  sf::Sprite* getSprite();
  bool setUpSpriteFromPath(std::string file_path);
  XY getSpriteCenter();

 private:
  sf::Sprite sprite;
  sf::Texture texture;
};

#endif // !RENDER_ELEMENT_H
