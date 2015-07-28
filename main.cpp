#include "PlayerCharacter.h"
#include "FunctionLib.h"

void PollEvent(sf::RenderWindow* pTarget);
void Render(sf::RenderWindow* pTarget);

sf::ContextSettings settings;

sf::RenderWindow window;
PlayerCharacter MyPlayer(500, 500, 150, 100);

KeyState KeysPressed;
sf::Clock GameClock;
float FrameTime;

int main()
{
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Heist", sf::Style::Default, settings);

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

    MyPlayer.SetDiretion(MyPlayer.DirectionToPoint(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
    MyPlayer.Move(KeysPressed, FrameTime);
    MyPlayer.Update(FrameTime);
}

void Render(sf::RenderWindow* pTarget)
{
    window.clear();
    MyPlayer.Render(pTarget);
    window.display();
}



