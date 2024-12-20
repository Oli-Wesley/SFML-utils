#include "Camera.h"
#include "RenderElement.h"
#include "RenderQueue.h"
#include "Structs.h"
#include <iostream>

Camera::Camera()
{
  resolution.x     = 1920;
  resolution.y     = 1080;
  view_rect.width  = 1920;
  view_rect.height = 1080;
  if (!render_texture.create(resolution.x, resolution.y))
  {
    std::cout << "ERROR: failed to create RenderTexture";
    throw;
  }
}

void Camera::setResolution(int x, int y)
{
  resolution.x = x;
  resolution.y = y;
  if (!render_texture.create(resolution.x, resolution.y))
  {
    std::cout << "ERROR: failed to create RenderTexture";
    throw;
  }
}

void Camera::setViewSize(int x, int y)
{
  view_rect.width  = x;
  view_rect.height = y;
}

void Camera::setCenterPosition(float x, float y)
{
  view_rect.x -= x + view_rect.width / 2;
  view_rect.y -= y + view_rect.height / 2;
}

void Camera::setOriginPosition(float x, float y) 
{
  view_rect.x = x;
  view_rect.y = y;
}

void Camera::modifyPosition(float x, float y)
{
  view_rect.x += x;
  view_rect.y += y;
}

Structs::Rect Camera::getView()
{
  return view_rect;
}

void Camera::setZoom(float new_zoom)
{
  
  if (new_zoom > 0.01)
  {
  scaleAroundCenter(zoom, new_zoom);
  zoom = new_zoom;
  }
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

void Camera::render(sf::RenderWindow& window)
{
  render_queue.sortRenderQueue();
  render_texture.clear(sf::Color(0, 0, 0, 0));
  Structs::XY windowResolution;
  windowResolution.x = window.getSize().x;
  windowResolution.y = window.getSize().y;
  // iterate over the render_queue and draw each element.
  for (int i = 0; i < render_queue.getRenderQueueLength(); i++)
  {
    // check on screen, if so, render, must do after applying the movements to
    // the base sprite.

    render_queue.getElementAtPosition(i)->sprite->ConvertToScreenSpaceByCamera(
      view_rect, resolution, windowResolution);

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
  drawToWindow(window);
}

void Camera::drawToWindow(sf::RenderWindow& window)
{
  sf::Texture texture = render_texture.getTexture();
  sf::Sprite render_texture_sprite(texture);
  Structs::XY resolution_to_display_factor;

  // scale to size of the display.
  resolution_to_display_factor.x = window.getSize().x / resolution.x;
  resolution_to_display_factor.y = window.getSize().y / resolution.y;

  render_texture_sprite.setScale(
    resolution_to_display_factor.x, resolution_to_display_factor.y);

  // std::cout << "camera res: (" << render_texture.getSize().x << ", "
  //           << render_texture.getSize().y << ") \n";

  // draw to display
  window.draw(render_texture_sprite);
}

void Camera::outputInfo()
{
  std::cout << "camera Center coords: (" << getCenter().x << ", "
            << getCenter().y << "), camera Rect: (" << getView().x << ", "
            << getView().y << ", " << getView().width << ", "
            << getView().height << "), Camera Zoom: (" << zoom << ")\n";
}

Structs::XY Camera::getCenter()
{
  Structs::XY center_coords;

  center_coords.x = view_rect.x + view_rect.width / 2;
  center_coords.y = view_rect.y + view_rect.height / 2;

  return center_coords;
}

void Camera::scaleAroundCenter(float old_scale, float new_scale)
{
  Structs::XY old_center = getCenter();
  view_rect.width /= old_scale;
  view_rect.height /= old_scale;

  view_rect.width *= new_scale;
  view_rect.height *= new_scale;

  Structs::XY new_center = getCenter();
  view_rect.x += old_center.x - new_center.x;
  view_rect.y += old_center.y - new_center.y;
}
