#include "Camera.h"
#include "RenderElement.h"
#include "RenderQueue.h"
#include <iostream>

Camera::Camera()
{
  resolution.x = 1920;
  resolution.y = 1080;
  if (!render_texture.create(resolution.x, resolution.y))
  {
    std::cout << "ERROR: failed to create RenderTexture";
    throw;
  }
}

void Camera::setResolution(int x, int y, sf::Window& window)
{
  resolution.x = x;
  resolution.y = y;
  if (!render_texture.create(resolution.x, resolution.y))
  {
    std::cout << "ERROR: failed to create RenderTexture";
    throw;
  }

  resolution_to_display_factor.x = window.getSize().x / resolution.x;
  resolution_to_display_factor.y = window.getSize().y / resolution.y;
}

Camera::XY Camera::getResolution()
{
  return resolution;
}

void Camera::setPosition(float x, float y)
{
  position.x = x;
  position.y = y;
}

void Camera::modifyPosition(float x, float y)
{
  position.x += x;
  position.y += y;
}

Camera::XY Camera::getPosition()
{
  return position;
}

void Camera::setZoom(float new_zoom)
{
  XY old_center = getCenter();
  if (new_zoom <= 0.0f)
    return;
  zoom          = new_zoom;
  XY new_center = getCenter();

  // modify adds the position to the current position
  modifyPosition(old_center.x - new_center.x, old_center.y - new_center.y);
}

void Camera::modifyZoom(float new_zoom)
{
  setZoom(zoom + new_zoom);
}

float Camera::getZoom()
{
  return zoom;
}

void Camera::addToRender(SpriteRenderElement& render_element)
{
  RenderQueue::RenderItem render_item;
  render_item.layer  = render_element.getLayer();
  render_item.sprite = &render_element;

  render_queue.addTorenderQueue(render_item);
}

void Camera::render()
{
  render_queue.sortRenderQueue();
  render_texture.clear(sf::Color(255, 0, 0));
  // iterate over the render_queue and draw each element.
  for (int i = 0; i < render_queue.getRenderQueueLength(); i++)
  {
    // apply position (currently zooms based on top left corner), TODO fix that.
    render_queue.getElementAtPosition(i)->sprite->ConvertToScreenSpaceByCamera(
      position.x,
      position.y,
      getCenter().x,
      getCenter().y,
      resolution.x,
      resolution.y,
      window_resolution.x,
      window_resolution.y,
      zoom);

    // check on screen, if so, render, must do after applying the movements to
    // the base sprite.
    if (render_queue.getElementAtPosition(i)->sprite->checkOnscreen(
          render_texture))
    {
      render_texture.draw(
        *render_queue.getElementAtPosition(i)->sprite->getSprite());
    }
    // else std::cout << "element " << i << " is offscreen, not drawing\n";
  }
  render_queue.reset();
  render_texture.display();
}

void Camera::drawToWindow(sf::RenderWindow& window)
{
  sf::Texture texture = render_texture.getTexture();
  sf::Sprite render_texture_sprite(texture);

  // scale to size of the display.
  resolution_to_display_factor.x = window.getSize().x / resolution.x;
  resolution_to_display_factor.y = window.getSize().y / resolution.y;

  render_texture_sprite.setScale(
    resolution_to_display_factor.x, resolution_to_display_factor.y);

  // std::cout << "camera res: (" << render_texture.getSize().x << ", "
  //           << render_texture.getSize().y << ") \n";

  // draw to display
  window.draw(render_texture_sprite);
  window.display();
}

void Camera::setWindowResolution(int x, int y)
{
  window_resolution.x = x;
  window_resolution.y = y;

  resolution_to_display_factor.x = x / resolution.x;
  resolution_to_display_factor.y = y / resolution.y;
}

Camera::XY Camera::getCenter()
{
  XY center_coords;

  center_coords.x = (position.x + (resolution.x / 2));
  center_coords.y = (position.y + (resolution.y / 2));

  return center_coords;
}
