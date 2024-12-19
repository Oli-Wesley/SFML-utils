#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  // create window and set up
  sf::RenderWindow window(sf::VideoMode(1080, 720), "My SFML game");
  window.setFramerateLimit(60);
  // A Clock starts counting as soon as it's created
  sf::Clock clock;
  Camera camera;
  int pix_size = 1;
  camera.setResolution(1080/pix_size, 720/pix_size, window);
  // center 540,360
  camera.setPosition(0, 0);
  camera.setZoom(0.5);

  // define sprites, then setTexture.
  SpriteRenderElement ball("../Data/Images/ball.png");
  SpriteRenderElement background("../Data/Images/background.png", 0);
  ball.setScale(1);
  ball.setPosition(
    window.getSize().x / 2,
    window.getSize().y / 2);


  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;

    // calculate delta time
    sf::Time time = clock.restart();
    float dt      = time.asSeconds();

    //'process inputs' element of the game loop
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::KeyPressed)
      {
      }
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::Resized)
      {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
      }
    }

    // update
    camera.modifyZoom(0.001);
    //std::cout << "camera coords (" << camera.getCenter().x << ", "
    //          << camera.getCenter().y << ")\n";


    // add all RenderElements to the camera to render.
    camera.addToRender(ball);
    camera.addToRender(background);

    // render to the camera's render texture, then draw that to the window.
    camera.render();
    camera.drawToWindow(window);
  }
  return 0;
}
