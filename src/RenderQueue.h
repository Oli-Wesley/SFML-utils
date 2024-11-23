#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H

#include <SFML/Graphics.hpp>


class RenderQueue
{
  struct RenderItem
  {
    sf::Sprite sprite;
    int layer = NULL;
  };


  int render_queue_length  = 0;
  RenderItem* render_queue = nullptr;  
  sf::RenderWindow& game_window;

 public:
  RenderQueue(sf::RenderWindow& window);
  bool render();
  bool addToRenderQueue(RenderItem);
  bool addToRenderQueue(sf::Sprite sprite, int layer);
  int getRenderQueueLength();

 private:
  bool sortRenderQueue();
  bool resetRenderQueue();
  void pushBack(RenderItem element);
};

#endif 