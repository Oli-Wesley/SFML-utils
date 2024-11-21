#include "RenderQueue.h"
#include <SFML/Graphics.hpp>

// constructor, saves the window value for later use.  
RenderQueue::RenderQueue(sf::RenderWindow& window) : game_window(window) 
{
    
}

// Public: sorts, then draws the render queue, starting with the lowest layer.
bool RenderQueue::render()
{
  sortRenderQueue();
  game_window.clear(sf::Color::Black);
  for (RenderQueue::RenderItem element : render_queue)
  {
    game_window.draw(element.sprite);
  }
  game_window.display();
  resetRenderQueue();
  return 1;
}

// Public: add to queue with a pre-made render item. 
bool RenderQueue::addToRenderQueue(RenderQueue::RenderItem render_item)
{
  render_queue.push_back(render_item);
  render_queue_length++;
  return 1;
}

// Public: add to queue with a seperate sprite and layer.
bool RenderQueue::addToRenderQueue(sf::Sprite sprite, int layer)
{
  RenderItem render_item;
  render_item.layer = layer;
  render_item.sprite = sprite;
  render_queue.push_back(render_item);
  render_queue_length++;
  return 1;
}

// doesnt work, not really needed so cant be bothered to implement for now.
bool RenderQueue::removeFromRenderQueue(RenderItem remove_render_item)
{
  //int index = 0;
  //for (RenderQueue::RenderItem element : render_queue)
  //{
  //   i dont know why this doesnt work, fix later.
  //   if (element == remove_render_item)
  //  {
  //    render_queue.erase(render_queue.begin()+index);
  //    return 1;
  //  }
  //  index++;
  //}
  return 0;
}

int RenderQueue::getRenderQueueLength()
{
  return render_queue_length;
}

// private: sort the render queue, this puts the queue in order ready for rendering. 
bool RenderQueue::sortRenderQueue()
{
  // simple bubble sort implimentation, sort the list based on layer. 
  bool changed = 1;
  
  RenderQueue::RenderItem hold;
  while (changed)
  {
    changed = 0;
    for (int index = 0 ; index < render_queue_length-1 ; index++)
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
  render_queue.clear();
  return 1;
}