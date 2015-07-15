#include "PlayerCharacter.h"

void PollEvent(sf::RenderWindow* pTarget);

sf::RenderWindow window(sf::VideoMode(1920, 1080), "Heist");

int main()
{
    while (window.isOpen())
        PollEvent(&window);
}

void PollEvent(sf::RenderWindow* pTarget)
{
    sf::Event event;

    while (pTarget->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            pTarget->clear();
        }
    }
}



