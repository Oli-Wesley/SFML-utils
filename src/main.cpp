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
  float pix_size = 1;
  camera.setResolution(window.getSize().x/pix_size, window.getSize().y/pix_size);
  camera.setViewSize(2160, 1440);
  camera.setOriginPosition(0, 0);
  camera.setZoom(1);

  // define sprites, then setTexture.
  SpriteRenderElement ball("../Data/Images/ball.png");
  SpriteRenderElement background("../Data/Images/background.png", 0);
  ball.setScale(2);
  ball.setPosition(window.getSize().x / 2, window.getSize().y / 2);
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
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::W)
        {
          camera.modifyPosition(0, -10);
        }
        else if (event.key.code == sf::Keyboard::S)
        {
          camera.modifyPosition(0, 10);
        }
        else if (event.key.code == sf::Keyboard::A)
        {
          camera.modifyPosition(-10, 0);
        }
        else if (event.key.code == sf::Keyboard::D)
        {
          camera.modifyPosition(10, 0);
        }
        else if (event.key.code == sf::Keyboard::Q)
        {
          camera.modifyZoom(-0.01);
        }
        else if (event.key.code == sf::Keyboard::E)
        {
          camera.modifyZoom(0.01);
        }
        else if (event.key.code == sf::Keyboard::Num1)
        {
          float pix_size = 1;
          camera.setResolution(
            window.getSize().x / pix_size, window.getSize().y / pix_size);
        }
        else if (event.key.code == sf::Keyboard::Num2)
        {
          float pix_size = 2;
          camera.setResolution(
            window.getSize().x / pix_size, window.getSize().y / pix_size);
        }
        else if (event.key.code == sf::Keyboard::Num3)
        {
          float pix_size = 5;
          camera.setResolution(
            window.getSize().x / pix_size, window.getSize().y / pix_size);
        }
        else if (event.key.code == sf::Keyboard::Num4)
        {
          float pix_size = 10;
          camera.setResolution(
            window.getSize().x / pix_size, window.getSize().y / pix_size);
        }
      }
    }

    // update 
    //camera.modifyZoom(+0.001);
    //camera.modifyPosition(1, 1);
    camera.outputInfo();
    // add all RenderElements to the camera to render.
    camera.addToRender(ball);
    camera.addToRender(background);

    // render to the camera's render texture, then draw that to the window.
    window.clear(sf::Color(255, 255, 0));
    camera.render(window);
    window.display();
  }
  return 0;
}
