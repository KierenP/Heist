#include "PlayerCharacter.h"
#include "FunctionLib.h"

void PollEvent(sf::RenderWindow* pTarget);
void Render(sf::RenderWindow* pTarget);

sf::RenderWindow window(sf::VideoMode(1920, 1080), "Heist");
PlayerCharacter MyPlayer(500, 500, 5, 100);

int main()
{
    sf::Texture MyTexture;

    if (!MyTexture.loadFromFile("PlaceHolderPlayer.png"))
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            MyPlayer.Move(LEFT, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            MyPlayer.Move(RIGHT, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            MyPlayer.Move(UP, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            MyPlayer.Move(DOWN, 1);
    }

    MyPlayer.UpdateSprite();
}

void Render(sf::RenderWindow* pTarget)
{
    window.clear();
    MyPlayer.Render(pTarget);
    window.display();
}



