#include "RenderQueue.h"
#include <SFML/Graphics.hpp>

// constructor, saves the window value for later use.
RenderQueue::RenderQueue(sf::RenderWindow& window) : game_window(window)
{
  delete[] render_queue;
  render_queue = new RenderItem[render_queue_length];
}

// Public: sorts, then draws the render queue, starting with the lowest layer.
bool RenderQueue::render()
{
  sortRenderQueue();
  game_window.clear(sf::Color::Black);
  for (int i = 0; i < render_queue_length; i++)
  {
    game_window.draw(render_queue[i].sprite);
  }
  game_window.display();
  resetRenderQueue();
  return 1;
}

// Public: add to queue with a pre-made render item.
bool RenderQueue::addToRenderQueue(RenderQueue::RenderItem render_item)
{
  pushBack(render_item);
  return 1;
}

// Public: add to queue with a seperate sprite and layer.
bool RenderQueue::addToRenderQueue(sf::Sprite sprite, int layer)
{
  RenderItem render_item;
  render_item.layer  = layer;
  render_item.sprite = sprite;
  pushBack(render_item);
  return 1;
}

int RenderQueue::getRenderQueueLength()
{
  return render_queue_length;
}

// private: sort the render queue, this puts the queue in order ready for
// rendering.
bool RenderQueue::sortRenderQueue()
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
  return 1;
}

// private: resets the render queue.
bool RenderQueue::resetRenderQueue()
{
  render_queue_length = 0;
  delete[] render_queue;
  render_queue = new RenderItem[render_queue_length];
  return 1;
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
  render_queue_length++;
  render_queue = new RenderItem[render_queue_length];

  // assign to temp, then delete temp;
  for (int i = 0; i < render_queue_length - 1; i++)
  {
    render_queue[i] = temp[i];
  }
  delete[] temp;

  render_queue[render_queue_length - 1] = element;
}
