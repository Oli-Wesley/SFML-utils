#include "RenderQueue.h"
#include <SFML/Graphics.hpp>

// constructor, saves the window value for later use.
RenderQueue::RenderQueue(sf::RenderWindow& window) : game_window(window)
{
  delete[] render_queue;
  render_queue = new RenderItem[render_queue_length];
}

// Public: sorts, then draws the render queue, starting with the lowest layer.
void RenderQueue::render()
{
  sortRenderQueue();
  game_window.clear(sf::Color::Black);
  for (int i = 0; i < render_queue_length; i++)
  {
    if (render_queue[i].sprite != nullptr)
    {
      game_window.draw(*render_queue[i].sprite);
    }
    else if (render_queue[i].text != nullptr)
    {
      game_window.draw(*render_queue[i].text);
    }
    else if (render_queue[i].circle_shape != nullptr)
    {
      game_window.draw(*render_queue[i].circle_shape);
    }
    else if (render_queue[i].convex_shape != nullptr)
    {
      game_window.draw(*render_queue[i].convex_shape);
    }
    else if (render_queue[i].rectangle_shape != nullptr)
    {
      game_window.draw(*render_queue[i].rectangle_shape);
    }
    else if (render_queue[i].vertex_array != nullptr)
    {
      game_window.draw(*render_queue[i].vertex_array);
    }
  }
  game_window.display();
  resetRenderQueue();
}

void RenderQueue::addTorenderQueue(RenderItem render_item)
{
  pushBack(render_item);
}

// add to render queue functions, each one takes a drawable object and a layer
void RenderQueue::addToRenderQueue(sf::Sprite& sprite, int layer)
{
  RenderItem render_item;
  render_item.layer  = layer;
  render_item.sprite = &sprite;
  pushBack(render_item);
}

void RenderQueue::addToRenderQueue(sf::Text& text, int layer)
{
  RenderItem render_item;
  render_item.layer = layer;
  render_item.text  = &text;
  pushBack(render_item);
}

void RenderQueue::addToRenderQueue(sf::CircleShape& circle_shape, int layer)
{
  RenderItem render_item;
  render_item.layer        = layer;
  render_item.circle_shape = &circle_shape;
  pushBack(render_item);
}

void RenderQueue::addToRenderQueue(sf::ConvexShape& convex_shape, int layer)
{
  RenderItem render_item;
  render_item.layer        = layer;
  render_item.convex_shape = &convex_shape;
  pushBack(render_item);
}

void RenderQueue::addToRenderQueue(
  sf::RectangleShape& rectangle_shape, int layer)
{
  RenderItem render_item;
  render_item.layer           = layer;
  render_item.rectangle_shape = &rectangle_shape;
  pushBack(render_item);
}

void RenderQueue::addToRenderQueue(sf::VertexArray& vertex_array, int layer)
{
  RenderItem render_item;
  render_item.layer        = layer;
  render_item.vertex_array = &vertex_array;
  pushBack(render_item);
}

int RenderQueue::getRenderQueueLength()
{
  return render_queue_length;
}

// private: sort the render queue, this puts the queue in order ready for
// rendering.
void RenderQueue::sortRenderQueue()
{
  // simple bubble sort implimentation, sort the list based on layer.
  bool changed = 1;

  RenderQueue::RenderItem hold;
  while (changed)
  {
    changed = 0;
    for (int index = 0; index < render_queue_length - 1; index++)
    {
      if (render_queue[index].layer > render_queue[index + 1].layer)
      {
        hold                    = render_queue[index];
        render_queue[index]     = render_queue[index + 1];
        render_queue[index + 1] = hold;
        changed                 = 1;
      }
    }
  }
}

// private: resets the render queue.
void RenderQueue::resetRenderQueue()
{
  render_queue_length = 0;
  delete[] render_queue;
  render_queue = new RenderItem[render_queue_length];
}

void RenderQueue::pushBack(RenderItem element)
{
  // create temp.
  RenderItem* temp = new RenderItem[render_queue_length];

  // assign temp to the current render queue;
  for (int i = 0; i < render_queue_length; i++)
  {
    temp[i] = render_queue[i];
  }

  // delete old array, create new one with larger size.
  delete[] render_queue;

  render_queue = new RenderItem[render_queue_length + 1];

  // assign to temp, then delete temp;
  for (int i = 0; i < render_queue_length; i++)
  {
    render_queue[i] = temp[i];
  }
  delete[] temp;
  render_queue[render_queue_length] = element;

  render_queue_length++;
}
