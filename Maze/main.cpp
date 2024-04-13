#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maze.h"
#include "Cell.h"

int main() {
    int columns = 50;
    int rows = 50;
    Maze Map(columns, rows);

    Cell* currentCell = Map.GetRandomCell();

    std::map<int, int[2]> neighbours;
    int neighbourX;
    int neighbourY;

    int randIndex;
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
            srand((unsigned int)time(NULL));
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

                            srand((unsigned int)time(NULL));
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

    
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}