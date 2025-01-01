#ifndef CAMERA_H
#define CAMERA_H
#include "RenderElement.h"
#include "RenderQueue.h"
#include "../DataStructures/Structs.h"
#include <SFML/Graphics.hpp>

class Camera
{
 public:
  Camera();

  // getter's and setters for various variables 
  void setResolution(int x, int y);
  void setViewSize(int x, int y);
  void setCenterPosition(float x, float y);
  void setOriginPosition(float x, float y);
  void modifyPosition(float x, float y);
  Structs::Rect getView();
  void setZoom(float new_zoom);
  void modifyZoom(float new_zoom);
  float getZoom();

  // rendering functions
  void addToRender(SpriteRenderElement& render_element);
  void render(sf::RenderWindow& window);
  void drawToWindow(sf::RenderWindow& window);

  Structs::XY getCenter();

  void outputInfo();

 private:
  RenderQueue render_queue;
  float zoom = 1;
  Structs::Rect view_rect;
  sf::RenderTexture render_texture;
  Structs::XY resolution;

  void scaleAroundCenter(float old_scale, float new_scale);
};

#endif