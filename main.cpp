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

TileEngine MyEngine;

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

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

	

	std::vector<Character> MyPlayerVec;

    MyTexture.loadFromFile("PlaceHolderPlayer.png");
    TileSet.loadFromFile("TileSet.png");

	Character MyPlayer(512, 512, MyTexture, HUMAN_CHARACTER, 0, GetWeaponStat(SMGWeapon), 150, 100);

	MyPlayerVec.push_back(MyPlayer);

	for (int i = 0; i < 1; i++)
	{
		Character MyPlayer2(rand() % 500, rand() % 500, MyTexture, AI_CHARACTER, 1, GetWeaponStat(SMGWeapon), 100, 100);
		MyPlayerVec.push_back(MyPlayer2);
	}

    std::vector<std::vector<int> > TileIDVec;
    std::vector<std::vector<bool> > SolidStateVec;

    for (unsigned int i = 0; i < MapHeight; i++)
    {
        std::vector<bool> boolRow;
        std::vector<int> intRow;

        for (unsigned int j = 0; j < MapWidth; j++)
        {
            intRow.push_back(rand() % 5);

            if (intRow[j] >= 1)
                intRow[j] = 1;

            if (intRow[j] == 0)
                boolRow.push_back(true);
            else
                boolRow.push_back(false);
        }

        SolidStateVec.push_back(boolRow);
        TileIDVec.push_back(intRow);
    }

    MyEngine.LoadFromParam(32, 32, MapWidth, MapHeight, TileSet, TileIDVec, SolidStateVec, 0, 0);

    TestLevel.SetPlayers(MyPlayerVec);
    TestLevel.SetTileEngine(MyEngine);
    TestLevel.SetTarget(&window);
    TestLevel.SetSpawnPoint(0, sf::Vector2f(150, 100));
    TestLevel.SetSpawnPoint(1, sf::Vector2f(300, 200));
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



