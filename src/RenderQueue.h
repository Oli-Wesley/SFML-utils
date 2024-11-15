#include <SFML/Graphics.hpp>
#include <string>
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

 public:
  bool render(sf::RenderWindow);
  bool addToRenderQueue(RenderItem);
  bool removeFromRenderQueue(RenderItem);
  int getRenderQueueLength();
 private:
  bool sortRenderQueue();
  bool resetRenderQueue();
};