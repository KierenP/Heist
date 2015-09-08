#include "LevelEntityManager.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void PollEvent();
void Render();
void Update();
void GenerateTestLevel();

unsigned int const MapWidth = 30;
unsigned int const MapHeight = 30;

sf::ContextSettings settings;
sf::RenderWindow window;
LevelEntityManager TestLevel;
KeyState KeysPressed;

Character MyPlayer;
Character MyPlayer2;
TileEngine MyEngine;

int main()
{
    srand (time(NULL));

    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Heist", sf::Style::Default, settings);

    GenerateTestLevel();

    while (window.isOpen())
    {
        PollEvent();
        Render();
    }
}

void GenerateTestLevel()
{
    sf::Texture MyTexture;
    sf::Texture TileSet;

    MyTexture.loadFromFile("PlaceHolderPlayer.png");
    TileSet.loadFromFile("TileSet.png");

    MyPlayer.SetTexture(MyTexture);
    MyPlayer.SetWeapon(GetWeaponStat(SMGWeapon));
    MyPlayer.SetHealth(100);
    MyPlayer.SetPosX(512);
    MyPlayer.SetPosY(512);
    MyPlayer.SetSpeed(150);
    MyPlayer.SetPlayerID(PlayerCharacter);
    MyPlayer.SetTeamId(0);

    MyPlayer2.SetTexture(MyTexture);
    MyPlayer2.SetWeapon(GetWeaponStat(SMGWeapon));
    MyPlayer2.SetHealth(100);
    MyPlayer2.SetPosX(256);
    MyPlayer2.SetPosY(256);
    MyPlayer2.SetSpeed(10);
    MyPlayer2.SetPlayerID(AiCharacter);
    MyPlayer.SetTeamId(1);

    std::vector<std::vector<int> > TileIDVec;
    std::vector<std::vector<bool> > SolidStateVec;

    for (unsigned int i = 0; i < MapHeight; i++)
    {
        std::vector<bool> boolRow;
        std::vector<int> intRow;

        for (unsigned int j = 0; j < MapWidth; j++)
        {
            intRow.push_back(rand() % 10);

            if (intRow[j] > 1)
                intRow[j] = 1;

            if (intRow[j] == 0)
                boolRow.push_back(true);
            else
                boolRow.push_back(false);
        }

        SolidStateVec.push_back(boolRow);
        TileIDVec.push_back(intRow);
    }

    MyEngine.LoadFromParam(32, 32, MapWidth, MapHeight, TileSet, TileIDVec, SolidStateVec, 64, 64);

    std::vector<Character*> MyPlayerVec;

    MyPlayerVec.push_back(&MyPlayer);
    MyPlayerVec.push_back(&MyPlayer2);

    TestLevel.SetPlayers(MyPlayerVec);
    TestLevel.SetTileEngine(MyEngine);
    TestLevel.SetTarget(&window);
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



