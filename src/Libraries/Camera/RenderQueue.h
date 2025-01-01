#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H

#include <SFML/Graphics.hpp>
#include "RenderElement.h"

class RenderQueue
{
 public:
  struct RenderItem
  {
    SpriteRenderElement* sprite                  = nullptr;
    //sf::Text* text                      = nullptr;
    //sf::CircleShape* circle_shape       = nullptr;
    //sf::ConvexShape* convex_shape       = nullptr;
    //sf::RectangleShape* rectangle_shape = nullptr;
    //sf::VertexArray* vertex_array       = nullptr;
    int layer                           = NULL;
  };
  RenderQueue();
  // void render();
  void addTorenderQueue(RenderItem render_item);
  //void addToRenderQueue(sf::Text& text, int layer);
  //void addToRenderQueue(sf::CircleShape& circle_shape, int layer);
  //void addToRenderQueue(sf::ConvexShape& convex_shape, int layer);
  //void addToRenderQueue(sf::RectangleShape& rectangle_shape, int layer);
  //void addToRenderQueue(sf::VertexArray& vertex_array, int layer);
  int getRenderQueueLength();
  RenderItem* getElementAtPosition(int position);
  void sortRenderQueue();
  void reset();

 private:
  void pushBack(RenderItem element);
  int render_queue_length  = 0;
  RenderItem* render_queue = nullptr;
};

#endif