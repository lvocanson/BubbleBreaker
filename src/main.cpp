#include <SFML/Graphics.hpp>
#include "Utils/Logger.h"
#include <iostream>

int main()
{
    Logger::Create(std::cout);
    Logger::Instance() << "Opening window...\n";

    sf::RenderWindow window;
    window.create(sf::VideoMode({1600u, 900u}), "BubbleBreaker");
    window.setFramerateLimit(144u);

    sf::Clock clock;

    while (window.isOpen())
    {
        // Window events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                Logger::Instance() << "Close event received. Closing window...\n";
                window.close();
            }
        }

        // Update
        float dt = clock.restart().asSeconds();

        // Draw
        window.clear();
        window.display();
    }
}
