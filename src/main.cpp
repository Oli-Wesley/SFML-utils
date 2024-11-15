#include <iostream>
#include <SFML/Graphics.hpp>
#include "RenderQueue.h"


int main()
{
    // create window and set up
    sf::RenderWindow window(sf::VideoMode(1080, 720), "My SFML game");
    window.setFramerateLimit(60);

    // A Clock starts counting as soon as it's created
    sf::Clock clock;

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

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
