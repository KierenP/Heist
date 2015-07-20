#include "PlayerCharacter.h"
#include "FunctionLib.h"

void PollEvent(sf::RenderWindow* pTarget);
void Render(sf::RenderWindow* pTarget);

sf::RenderWindow window(sf::VideoMode(1920, 1080), "Heist");
PlayerCharacter MyPlayer(500, 500, 256, 100);

KeyState ArrowsPressed;
sf::Clock GameClock;
float FrameTime;

int main()
{
    sf::Texture MyTexture;

    if (!MyTexture.loadFromFile("PlaceHolderPlayer.png"))
        return -1;

    MyPlayer.SetTexture(MyTexture);

    while (window.isOpen())
    {
        FrameTime = GameClock.restart().asSeconds();

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            ArrowsPressed.LeftPressed = true;
        else
            ArrowsPressed.LeftPressed = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            ArrowsPressed.RightPressed = true;
        else
            ArrowsPressed.RightPressed = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            ArrowsPressed.UpPressed = true;
        else
            ArrowsPressed.UpPressed = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            ArrowsPressed.DownPressed = true;
        else
            ArrowsPressed.DownPressed = false;
    }
    MyPlayer.Move(ArrowsPressed, FrameTime);
    MyPlayer.UpdateSprite();
}

void Render(sf::RenderWindow* pTarget)
{
    window.clear();
    MyPlayer.Render(pTarget);
    window.display();
}



