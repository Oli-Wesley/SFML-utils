#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  // create window and set up
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "My SFML game");
  window.setFramerateLimit(60);
  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  // setup camera
  Camera camera;
  // setup camera, viewsize and resolution can be different, however they should
  // be the same aspect ratio otherwise things appear stretched.
  camera.setResolution(1920, 1080);
  camera.setViewSize(1920, 1080);
  // set position (can be center or origin)
  camera.setCenterPosition(0, 0);

  // setup sprites with path and (optional) layer
  SpriteRenderElement test_square("../Data/Images/Test_Square.png", 500);
  SpriteRenderElement test_square_red(
    "../Data/Images/Test_Square_Red.png", 500);
  SpriteRenderElement test_square_green(
    "../Data/Images/Test_Square_Green.png", 500);

  // set positions on 2 corners and center of the camera's position.
  test_square.setPosition(
    camera.getCenter().x - test_square.getSprite()->getLocalBounds().width / 2,
    camera.getCenter().y -
      test_square.getSprite()->getLocalBounds().height / 2);

  test_square_red.setPosition(
    -camera.getView().width / 2, -camera.getView().height / 2);

  test_square_green.setPosition(
    camera.getView().width / 2 -
      test_square.getSprite()->getLocalBounds().width,
    camera.getView().height / 2 -
      test_square.getSprite()->getLocalBounds().height);

  // scene setup
  // define Sprites:
  SpriteRenderElement clouds("../Data/Images/Clouds.png", 2);
  SpriteRenderElement grass("../Data/Images/grass.png", 4);
  SpriteRenderElement house("../Data/Images/House.png", 3);
  SpriteRenderElement mountains("../Data/Images/Mountains.png", 1);
  SpriteRenderElement people("../Data/Images/people.png", 5);

  clouds.setMovePercentage(0.4);
  house.setMovePercentage(0.6);
  mountains.setMovePercentage(0.2);
  grass.setMovePercentage(1);
  people.setMovePercentage(0.01);

  mountains.setScale(1);
  people.setScale(0.25);
  clouds.setScale(0.5);
  grass.setScale(0.4);
  house.setScale(0.4);

  mountains.setPosition(-1920, -540);
  clouds.setPosition(-960, -520);
  people.setPosition(-200, 280);
  grass.setPosition(-420, 110);
  house.setPosition(-920, 110);

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

      // controls for moving zooming, and changing the res of the camera.
      if (event.type == sf::Event::KeyPressed)
      {
        if (event.key.code == sf::Keyboard::Escape)
        {
          window.close();
        }
        else if (event.key.code == sf::Keyboard::W)
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

    // update (would be moving characters ect...)

    // Render

    // add all RenderElements to the camera to render.
    camera.addToRender(test_square);
    camera.addToRender(test_square_red);
    camera.addToRender(test_square_green);

    camera.addToRender(clouds);
    camera.addToRender(grass);
    camera.addToRender(house);
    camera.addToRender(mountains);
    camera.addToRender(people);

    // render to the camera's render texture, then draw that to the window.
    window.clear(sf::Color(255, 255, 0));
    // draw to the window (has a transparent background for areas that don't
    // have anything given.
    camera.render(window);
    // draw ui ontop of what the camera sees as usual:

    // draw everything to the display
    window.display();
  }
  return 0;
}
