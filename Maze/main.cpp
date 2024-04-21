#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Cell.h"
#include "Math.h"
#include "Player.h"

int main() {
    int columns = 7;
    int rows = 7;

    Maze map(columns, rows);
    map.GenerateMaze();


    Player player;
    player.Initialize();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Maze-Game");

    map.Load();

    map.GenerateStartRoom();
    map.GenerateEndRoom();

    player.Load();

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