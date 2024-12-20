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
  
  // setup camera
  Camera camera;
  camera.setResolution(1920,1080);
  camera.setViewSize(1920, 1080);
  camera.setOriginPosition(0, 0);
  camera.setZoom(1);

  // define Sprites:
  SpriteRenderElement clouds("../Data/Images/Clouds.png");
  SpriteRenderElement grass("../Data/Images/grass.png");
  SpriteRenderElement house("../Data/Images/House.png");
  SpriteRenderElement mountains("../Data/Images/Mountains.png");
  SpriteRenderElement people("../Data/Images/people.png");


  mountains.setLayer(0);
  clouds.setLayer(1);
  house.setLayer(2);
  people.setLayer(3);
  grass.setLayer(4);

  mountains.setMovePercentage(0.2);
  clouds.setMovePercentage(0.5);
  house.setMovePercentage(0.6);
  people.setMovePercentage(1);
  grass.setMovePercentage(0.9);

  mountains.setScale(1);
  people.setScale(0.25);
  clouds.setScale(0.3);
  grass.setScale(0.2);
  house.setScale(0.4);

  clouds.setPosition(0, 30);
  people.setPosition(500, 800);
  grass.setPosition(0, 870);
  house.setPosition(0, 650);


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
    


    // Render

    // add all RenderElements to the camera to render.
    camera.addToRender(clouds);
    camera.addToRender(grass);
    camera.addToRender(house);
    camera.addToRender(mountains);
    camera.addToRender(people);

    // render to the camera's render texture, then draw that to the window.
    window.clear(sf::Color(255, 255, 0));
    camera.render(window);
    window.display();
  }
  return 0;
}
