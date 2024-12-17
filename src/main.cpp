#include <iostream>
#include <SFML/Graphics.hpp>
#include "RenderQueue.h"
#include "SpriteUtils.h"


int main()
{
    // create window and set up
    sf::RenderWindow window(sf::VideoMode(1080, 720), "My SFML game");
    window.setFramerateLimit(60);
    // A Clock starts counting as soon as it's created
    sf::Clock clock;
    RenderQueue render_queue(window);

    // define textures, then assign to sprite.
    sf::Texture bird_texture;
    sf::Texture ball_texture;
    sf::Texture background_texture;
    sf::Texture cat_texture;
    sf::Sprite bird = SpriteUtils::getSpriteFromPath("../Data/Images/bird.png", bird_texture);
    sf::Sprite ball = SpriteUtils::getSpriteFromPath("../Data/Images/ball.png", ball_texture);
    sf::Sprite background = SpriteUtils::getSpriteFromPath(
      "../Data/Images/background.png", background_texture);
    sf::Sprite cat = SpriteUtils::getSpriteFromPath(
      "../Data/Images/Cat_Right.png", cat_texture);

    sf::Font font = SpriteUtils::getFontFromPath("../Data/Fonts/OpenSans-Bold.ttf");

    sf::Text text1 = SpriteUtils::setupText(
      font, "Hello World!", 100, sf::Color(150, 0, 255), 0, 0);


    // set position (for testing), would usually be handled by the object class.
    bird.setPosition(10,10);
    ball.setPosition(20,20);
    background.setPosition(0, 0);
    cat.setPosition(20, 10);

    // Game loop: run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        //calculate delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        //'process inputs' element of the game loop
        while (window.pollEvent(event))
        {
          if (event.type == sf::Event::KeyPressed)
          {
          }
           // "close requested" event: we close the window
           if (event.type == sf::Event::Closed)
           window.close();
        }


        // Test add to render Queue, can be done anywhere, in any order. 
        render_queue.addToRenderQueue(text1, 30);
        render_queue.addToRenderQueue(bird, 1);
        render_queue.addToRenderQueue(ball, 2);
        render_queue.addToRenderQueue(background, 0);
        render_queue.addToRenderQueue(cat, 3);

        // render, done at the end, renders in order with the lowest layer first. 
        render_queue.render();
        
    }
    return 0;
}
