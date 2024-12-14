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

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                Logger::Instance() << "Close event received. Closing window...\n";
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
