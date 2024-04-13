#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Cell.h"
#include <random>

int main() {
    int columns = 10;
    int rows = 10;
    Maze Map(columns, rows);

    Cell* currentCell = Map.GetRandomCell();

    std::map<int, int[2]> neighbours;
    int neighbourX;
    int neighbourY;

    int randIndex;
    srand(time(NULL));

    std::vector<std::vector<int>> unvisitedNeighbours;
    std::vector<std::vector<int>> visitedNeighbours;

    while (currentCell != NULL) {
        neighbours = currentCell->GetAllNeighbours();
        int i = 0;
        for (auto item = neighbours.begin(); item != neighbours.end(); item++) {
            if (Map.cells[item->second[0]][item->second[1]].GetNumberLinks() == 0) {
                unvisitedNeighbours.push_back(std::vector<int>());
                unvisitedNeighbours[i].push_back(item->second[0]);
                unvisitedNeighbours[i].push_back(item->second[1]);
                i++;
            }
        }

        if (unvisitedNeighbours.size() > 0) {
            randIndex = rand() % unvisitedNeighbours.size();
            neighbourX = unvisitedNeighbours[randIndex][0];
            neighbourY = unvisitedNeighbours[randIndex][1];


            currentCell->link(Map.cells[neighbourX][neighbourY]);
            currentCell = &Map.cells[neighbourX][neighbourY];
            std::vector<std::vector<int>>().swap(unvisitedNeighbours);
        }
        else {
            currentCell = NULL;
            for (size_t y = 0; y < rows; y++) {
                for (size_t x = 0; x < columns; x++) {

                    if (Map.cells[x][y].GetNumberLinks() == 0) {
                        i = 0;
                        neighbours = Map.cells[x][y].GetAllNeighbours();
                        for (auto item = neighbours.begin(); item != neighbours.end(); item++) {
                            if (Map.cells[item->second[0]][item->second[1]].GetNumberLinks() != 0) {

                                visitedNeighbours.push_back(std::vector<int>());
                                visitedNeighbours[i].push_back(item->second[0]);
                                visitedNeighbours[i].push_back(item->second[1]);
                                i++;
                            }
                        }

                        if (visitedNeighbours.size() > 0) {
                            currentCell = &Map.cells[x][y];

                            randIndex = rand() % visitedNeighbours.size();

                            neighbourX = visitedNeighbours[randIndex][0];
                            neighbourY = visitedNeighbours[randIndex][1];

                            currentCell->link(Map.cells[neighbourX][neighbourY]);
                            std::vector<std::vector<int>>().swap(visitedNeighbours);
                            break;
                        }
                    }
                }
            }
        }
    }

    for (size_t y = 0; y < rows; y++)
    {
        std::cout << std::endl;
        for (size_t x = 0; x < columns; x++)
        {
            std::cout << Map.cells[x][y].GetNumberLinks();
        }
    }

    std::cout << std::endl;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Maze-Game");

  

    sf::Texture cellTexture;
    
    int cellTextureHeight = 96;
    int cellTextureWight = 96;
    int distanceBetweenTexture = 32;


    if (cellTexture.loadFromFile("../Assets/Maze/Stylesheet.png")) {
        std::cout << "loaded" << std::endl;
    }
    else {
        std::cout << "Failed to loaded!" << std::endl;
    }
    
    for (size_t y = 0; y < rows; y++)
    {
        for (size_t x = 0; x < columns; x++)
        {
            int xIndex = 3;
            int yIndex = 3;
            bool left = 0;
            bool right = 0;
            bool up = 0;
            bool bottom = 0;
            std::vector<std::vector<int>> links = Map.cells[x][y].GetLinks();
            std::map<int, int[2]> allNeighbours = Map.cells[x][y].GetAllNeighbours();

            for (size_t i = 0; i < links.size(); i++) {
                for (auto item = allNeighbours.begin(); item != allNeighbours.end(); item++) {
                    if (links[i][0] == item->second[0] && links[i][1] == item->second[1]) {
                        switch (item->first) {
                        case 1:
                            bottom = 1;
                            break;
                        case 2:
                            right = 1;
                            break;
                        case 3:
                            up = 1;
                            break;
                        case 4:
                            left = 1;
                            break;
                        default:
                            break;
                        }
                    }
                }
            }

            if (left == 1 && right == 1 && up == 1 && bottom == 1) {
                xIndex = 0;
                yIndex = 0;
            }
            else if (left == 1 && up == 1&& bottom == 1 && right == 0) {
                xIndex = 1;
                yIndex = 0;
            }
            else if (left == 0 && up == 1 && bottom == 1 && right == 1) {
                xIndex = 2;
                yIndex = 0;
            }
            else if (left == 0 && up == 1 && bottom == 1 && right == 0) {
                xIndex = 3;
                yIndex = 0;
            }
            else if (left == 1 && up == 1 && bottom == 0 && right == 1) {
                xIndex = 0;
                yIndex = 1;
            }
            else if (left == 1 && up == 1 && bottom == 0 && right == 0) {
                xIndex = 1;
                yIndex = 1;
            }
            else if (left == 0 && up == 1 && bottom == 0 && right == 1) {
                xIndex = 2;
                yIndex = 1;
            }
            else if (left == 0 && up == 1 && bottom == 0 && right == 0) {
                xIndex = 3;
                yIndex = 1;
            }
            else if (left == 1 && up == 0 && bottom == 1 && right == 1) {
                xIndex = 0;
                yIndex = 2;
            }
            else if (left == 1 && up == 0 && bottom == 1 && right == 0) {
                xIndex = 1;
                yIndex = 2;
            }
            else if (left == 0 && up == 0 && bottom == 1 && right == 1) {
                xIndex = 2;
                yIndex = 2;
            }
            else if (left == 0 && up == 0 && bottom == 1 && right == 0) {
                xIndex = 3;
                yIndex = 2;
            }
            else if (left == 1 && up == 0 && bottom == 0 && right == 1) {
                xIndex = 0;
                yIndex = 3;
            }
            else if (left == 1 && up == 0 && bottom == 0 && right == 0) {
                xIndex = 1;
                yIndex = 3;
            }
            else if (left == 0 && up == 0 && bottom == 0 && right == 1) {
                xIndex = 2;
                yIndex = 3;
            }


            Map.cells[x][y].GetSprite().setTexture(cellTexture);
            Map.cells[x][y].GetSprite().setTextureRect(sf::IntRect((cellTextureHeight + distanceBetweenTexture) * xIndex, (cellTextureHeight + distanceBetweenTexture) * yIndex, cellTextureWight, cellTextureHeight));
            Map.cells[x][y].GetSprite().setPosition(x * cellTextureWight, y * cellTextureHeight);;
        }
    }

    while (window.isOpen()) {

        sf::Event event;        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        for (size_t y = 0; y < rows; y++)
        {
            for (size_t x = 0; x < columns; x++)
            {
                window.draw(Map.cells[x][y].GetSprite());
            }
        }
        window.display();
    }

    return 0;
}