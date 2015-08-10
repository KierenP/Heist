#include "PlayerCharacter.h"
#include "FunctionLib.h"
#include "TileEngine.h"
#include "LevelEntityManager.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void PollEvent();
void Render();
void Update();
void GenerateTestLevel();

sf::ContextSettings settings;

sf::RenderWindow window;

LevelEntityManager TestLevel;

KeyState KeysPressed;

int main()
{
    srand (time(NULL));

    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Heist", sf::Style::Default, settings);

    GenerateTestLevel();

    PlayerCharacter MyPlayer(500, 500, 150, 100);
    TileEngine MyEngine;
    sf::Texture MyTexture;
    sf::Texture TileSet;

    MyTexture.loadFromFile("PlaceHolderPlayer.png");
    TileSet.loadFromFile("TileSet.png");

    MyPlayer.SetTexture(MyTexture);
    MyPlayer.SetWeapon(GetWeaponStat(SMGWeapon));

    std::vector<std::vector<int> > TileIDVec;
    std::vector<std::vector<bool> > SolidStateVec;

    for (int i = 0; i < 100; i++)
    {
        std::vector<bool> boolRow;
        std::vector<int> intRow;

        for (int j = 0; j < 100; j++)
        {
            boolRow.push_back(rand() % 2);
            intRow.push_back(rand() % 1 + 1);
        }

        SolidStateVec.push_back(boolRow);
        TileIDVec.push_back(intRow);
    }

    MyEngine.LoadFromParam(0, 0, 32, 32, 100, 100, TileSet, TileIDVec, SolidStateVec);

    TestLevel.SetPlayer(MyPlayer);
    TestLevel.SetTileEngine(MyEngine);
    TestLevel.SetTarget(&window);

    while (window.isOpen())
    {
        PollEvent();
        Render();
    }
}

void GenerateTestLevel()
{

}

void PollEvent()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    Update();
}

void Update()
{
    KeysPressed.LMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    KeysPressed.LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    KeysPressed.RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    KeysPressed.UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    KeysPressed.DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    TestLevel.Update(KeysPressed);
}

void Render()
{
    window.clear();
    TestLevel.Render();
    window.display();
}



