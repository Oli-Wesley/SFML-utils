#include "RenderQueue.h"
#include <SFML/Graphics.hpp>

// render queue utils
bool RenderQueue::render(sf::RenderWindow window)
{
  sortRenderQueue();
  for (RenderQueue::RenderItem element : render_queue)
  {
    window.draw(element.sprite);
  }
  resetRenderQueue();
  return 1;
}

bool RenderQueue::addToRenderQueue(RenderQueue::RenderItem render_item)
{
  render_queue.push_back(render_item);
  render_queue_length++;
  return 1;
}

bool RenderQueue::removeFromRenderQueue(RenderItem remove_render_item)
{
  int index = 0;
  for (RenderQueue::RenderItem element : render_queue)
  {
    // i dont know why this doesnt work, fix later.
    // if (element == remove_render_item)
    //{
    //  render_queue.erase(render_queue.begin()+index);
    //  return 1;
    //}
    index++;
  }
  return 0;
}

int RenderQueue::getRenderQueueLength()
{
  return render_queue_length;
}

bool RenderQueue::sortRenderQueue()
{
  // bubble sort
  bool changed = 1;
  int index;
  RenderQueue::RenderItem hold;
  while (changed)
  {
    index   = 0;
    changed = 0;
    for (RenderQueue::RenderItem element : render_queue)
    {
      if (render_queue[index].layer > render_queue[index + 1].layer)
      {
        hold                    = render_queue[index];
        render_queue[index]     = render_queue[index + 1];
        render_queue[index + 1] = hold;
        changed                 = 1;
      }
      index++;
    }
  }
  return 1;
}

bool RenderQueue::resetRenderQueue()
{
  render_queue_length = 0;
  render_queue.clear();
  return 1;
}