#include <SFML/Graphics.hpp>
#include <vector>


class RenderQueue
{
  struct RenderItem
  {
    sf::Sprite sprite;
    int layer = NULL;
  };

  std::vector<RenderItem> render_queue;
  int render_queue_length = 0;
  sf::RenderWindow& game_window;

 public:
  RenderQueue(sf::RenderWindow &window);
  bool render();
  bool addToRenderQueue(RenderItem);
  bool addToRenderQueue(sf::Sprite sprite, int layer);
  bool removeFromRenderQueue(RenderItem);
  int getRenderQueueLength();

 private:
  bool sortRenderQueue();
  bool resetRenderQueue();
};