#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"
#include "Maze.h"
#include "Cell.h"

int main() {
    int columns = 10;
    int rows = 10;

    Maze map(columns, rows);
    map.GenerateMaze();
    map.Load();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Maze-Game");

    while (window.isOpen()) {

        sf::Event event;        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        map.Draw(window);
        window.display();
    }

    return 0;
}