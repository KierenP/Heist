#include "PlayerCharacter.h"

void PollEvent(sf::RenderWindow* pTarget);
void Render(sf::RenderWindow* pTarget);

sf::RenderWindow window(sf::VideoMode(1920, 1080), "Heist");
PlayerCharacter MyPlayer(500, 500, 5, 100);

int main()
{
    sf::Texture MyTexture;

    if (!MyTexture.loadFromFile("C:\\Users\\Kieren\\Documents\\GitHub\\Heist\\PlaceHolderPlayer.png"));
        return -1;

    MyPlayer.SetTexture(MyTexture);

    while (window.isOpen())
    {
        PollEvent(&window);
        Render(&window);
    }
}

void PollEvent(sf::RenderWindow* pTarget)
{
    sf::Event event;

    while (pTarget->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    MyPlayer.UpdateSprite();
}

void Render(sf::RenderWindow* pTarget)
{
    window.clear();
    window.display();
    MyPlayer.Render(pTarget);
}



