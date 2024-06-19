#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Maze.h"
#include "Cell.h"
#include "Math.h"
#include "Player.h"
#include "Menu.h"
#include "End.h"
#include "Start.h"

int main() {

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

    startgame(window);

    End end;
    end.Initialize();
    end.Load();

    while (end.GetIsMenu()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        end.Update(window);
        end.Draw(window);
    }

    return 0;
}