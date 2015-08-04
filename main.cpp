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
    MyPlayer.SetWeapon(GetWeaponStat(RifleWeapon));

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

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                KeysPressed.LMBPressed = true;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                KeysPressed.LMBPressed = false;
            }
        }

        KeysPressed.LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        KeysPressed.RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        KeysPressed.UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        KeysPressed.DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    }

    MyPlayer.SetDiretion(ToDegrees(DirectionToPoint(MyPlayer.GetPosX(), MyPlayer.GetPosY(), sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)));
    MyPlayer.Update(FrameTime, KeysPressed);
}

void Render(sf::RenderWindow* pTarget)
{
    window.clear();
    MyPlayer.Render(pTarget);
    window.display();
}



