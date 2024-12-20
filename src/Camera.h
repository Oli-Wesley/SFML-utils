#ifndef CAMERA_H
#define CAMERA_H
#include "RenderElement.h"
#include "RenderQueue.h"
#include <SFML/Graphics.hpp>

class Camera
{
 public:
  struct XY
  {
    float x = 0;
    float y = 0;
  };
  Camera();

  void setResolution(int x, int y, sf::Window & window);
  XY getResolution();

  void setPosition(float x, float y);
  void modifyPosition(float x, float y);
  XY getPosition();

  void setZoom(float new_zoom);
  void modifyZoom(float new_zoom);
  float getZoom();

  void addToRender(SpriteRenderElement& render_element);
  void render();
  void drawToWindow(sf::RenderWindow& window);

  void setWindowResolution(int x, int y);

  XY getCenter();

 private:
  RenderQueue render_queue;
  float zoom = 1;
  XY position;
  XY center_coords;
  sf::RenderTexture render_texture;
  XY resolution;
  XY window_resolution;
  XY resolution_to_display_factor;
};

#endif