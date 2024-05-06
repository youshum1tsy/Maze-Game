#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Cell.h"
#include "Math.h"
#include "Player.h"
#include "Menu.h"

int main() {
    int columns = 31;
    int rows = 31;

    Maze map(columns, rows);
    map.GenerateMaze();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Maze-Game");

    Menu menu;
    menu.Initialize();
    menu.Load();
    while (menu.GetIsMenu()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        menu.Update(window);
        menu.Draw(window);
    }

    Player player;
    player.Initialize(columns, rows);
    player.Load();

    map.Load();
    map.GenerateStartRoom();
    map.GenerateEndRoom();
    

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTimeTimer = clock.restart();
        float deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.Update(map.cells, map.startCell, map.endCell, deltaTime);

        window.clear(sf::Color::Black);
        map.Draw(window);
        player.Draw(window);

        window.display();
    }
    return 0;
}