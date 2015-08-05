#include "PlayerCharacter.h"
#include "FunctionLib.h"
#include "TileEngine.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void PollEvent(sf::RenderWindow* pTarget);
void Render(sf::RenderWindow* pTarget);
void UpdatePlayer();

sf::ContextSettings settings;

sf::RenderWindow window;
PlayerCharacter MyPlayer(500, 500, 150, 100);
TileEngine MyEngine;

KeyState KeysPressed;
sf::Clock GameClock;
float FrameTime;

int main()
{
    srand (time(NULL));

    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Heist", sf::Style::Default, settings);

    sf::Texture MyTexture;

    if (!MyTexture.loadFromFile("PlaceHolderPlayer.png"))
        return -1;

    MyPlayer.SetTexture(MyTexture);
    MyPlayer.SetWeapon(GetWeaponStat(SMGWeapon));

    sf::Texture TileSet;
    TileSet.loadFromFile("TileSet.png");

    std::vector<std::vector<int> > TileIDVec;
    std::vector<std::vector<bool> > SolidStateVec;

    for (int i = 0; i < 50; i++)
    {
        std::vector<bool> Row;

        for (int j = 0; j < 50; j++)
        {
            Row.push_back(rand() % 2);
        }

        SolidStateVec.push_back(Row);
    }

    for (int i = 0; i < 50; i++)
    {
        std::vector<int> Row;

        for (int j = 0; j < 50; j++)
        {
            Row.push_back(rand() % 32);
        }

        TileIDVec.push_back(Row);
    }

    MyEngine.LoadFromParam(0, 0, 64, 64, 50, 50, TileSet, TileIDVec, SolidStateVec);

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
    }

    UpdatePlayer();
}

void UpdatePlayer()
{
    KeysPressed.LMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    KeysPressed.LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    KeysPressed.RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    KeysPressed.UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    KeysPressed.DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    MyPlayer.SetDiretion(ToDegrees(DirectionToPoint(MyPlayer.GetPosX(), MyPlayer.GetPosY(), sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)));
    MyPlayer.Update(FrameTime, KeysPressed);
}

void Render(sf::RenderWindow* pTarget)
{
    window.clear();
    MyEngine.Render(pTarget);
    MyPlayer.Render(pTarget);
    window.display();
}



