#include "Camera.h"
#include "RenderElement.h"
#include "RenderQueue.h"
#include "../DataStructures/Structs.h"
#include <iostream>

// default setup for camera.
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

// sets the camera render resolution (not view size)
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

// change view size, scales around the center to a given size.
void Camera::setViewSize(int x, int y)
{
  Structs::XY old_center = getCenter();

  view_rect.width  = x;
  view_rect.height = y;

  Structs::XY new_center = getCenter();
  view_rect.x += old_center.x - new_center.x;
  view_rect.y += old_center.y - new_center.y;
}

// moves the camera center to a given position.
void Camera::setCenterPosition(float x, float y)
{
  view_rect.x = x - view_rect.width / 2;
  view_rect.y = y - view_rect.height / 2;
}

// sets the camera's top left corner to a given position.
void Camera::setOriginPosition(float x, float y)
{
  view_rect.x = x;
  view_rect.y = y;
}

// incriments position by a given value.
void Camera::modifyPosition(float x, float y)
{
  view_rect.x += x;
  view_rect.y += y;
}

// returns the camera's current view
Structs::Rect Camera::getView()
{
  return view_rect;
}

// sets the zoom to a given value
void Camera::setZoom(float new_zoom)
{
  if (new_zoom > 0.01)
  {
    scaleAroundCenter(zoom, new_zoom);
    zoom = new_zoom;
  }
}

// incriments zoom by a given amount.
void Camera::modifyZoom(float new_zoom)
{
  setZoom(zoom + new_zoom);
}

// retuns current zoom value
float Camera::getZoom()
{
  return zoom;
}

// adds a SpriteRenderElement to the camera's render queue, needs to be done
// every frame the element want's to be drawn
void Camera::addToRender(SpriteRenderElement& render_element)
{
  RenderQueue::RenderItem render_item;
  render_item.layer  = render_element.getLayer();
  render_item.sprite = &render_element;

  render_queue.addTorenderQueue(render_item);
}

// Renders the camera's render queue to a given window
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
    /*  else std::cout << "element " << i << " is offscreen, not drawing\n";*/
  }
  render_queue.reset();
  render_texture.display();
  drawToWindow(window);
}

// scale's the camera's render texture to the size of the window. 
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

// returns the camera's current center.
Structs::XY Camera::getCenter()
{
  Structs::XY center_coords;

  center_coords.x = view_rect.x + view_rect.width / 2;
  center_coords.y = view_rect.y + view_rect.height / 2;

  return center_coords;
}

// debug tool for outputting the camera's current info
void Camera::outputInfo()
{
  std::cout << "camera Center coords: (" << getCenter().x << ", "
            << getCenter().y << "), camera Rect: (" << getView().x << ", "
            << getView().y << ", " << getView().width << ", "
            << getView().height << "), Camera Zoom: (" << zoom << ")\n";
}

// private helper for changing zoom levels.
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
