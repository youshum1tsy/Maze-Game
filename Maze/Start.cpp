#include <iostream>
#include <fstream>
#include "Start.h"
#include "Maze.h"
#include "Player.h"

void startgame(sf::RenderWindow& window) {
    int columns = 21;
    int rows = 21;

    Maze map(columns, rows);
    map.GenerateMaze();

    Player player;
    player.Initialize(columns, rows);
    player.Load();

    map.Load();
    map.GenerateStartRoom();
    map.GenerateEndRoom();

    std::string timer;
    sf::Clock clock;
    bool isEnd = 0;

    sf::Text result;
    
    while (window.isOpen()) {
        sf::Time deltaTimeTimer = clock.restart();
        float deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.Update(map.cells, map.startCell, map.endCell, deltaTime, isEnd, timer, window);
        
        if (isEnd) {
            
            std::string filename = "../Scores/score.txt";
            std::ifstream inFile(filename);
            std::vector<float> times;
            std::string line;
            int counter = 0;
            
            while (std::getline(inFile, line) && counter != 10) {
                times.push_back(std::stof(line));
                counter++;
            }

            inFile.close();
            times.push_back(std::stof(timer));
            std::sort(times.begin(), times.end());

            std::ofstream outFile(filename);

            if (!outFile) {
                std::cout << "Error when opening file: " << filename << std::endl;
            }

            for (float time : times) {
                outFile << time << std::endl;
            }
            outFile.close();

            filename = "../Scores/lastTime.txt";
            std::ofstream outLastTimer(filename);
            outLastTimer << timer << std::endl;
            outLastTimer.close();

            window.clear(sf::Color::Black);
            break;
        }

        window.clear(sf::Color::Black);
        map.Draw(window);
        player.Draw(window);
        window.display();
    }
}