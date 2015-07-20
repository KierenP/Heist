#include "PlayerCharacter.h"
#include "FunctionLib.h"

void PollEvent(sf::RenderWindow* pTarget);
void Render(sf::RenderWindow* pTarget);

sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Heist");
PlayerCharacter MyPlayer(500, 500, 256, 100);

KeyState KeysPressed;
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
        PollEvent(&window);
        Render(&window);

        FrameTime = GameClock.restart().asSeconds();
    }
}

void PollEvent(sf::RenderWindow* pTarget)
{
    sf::Event event;

    while (pTarget->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        KeysPressed.LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        KeysPressed.RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        KeysPressed.UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        KeysPressed.DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    }
    MyPlayer.Move(KeysPressed, FrameTime);
    MyPlayer.UpdateSprite();
}

void Render(sf::RenderWindow* pTarget)
{
    window.clear();
    MyPlayer.Render(pTarget);
    window.display();
}



