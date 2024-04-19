#include "Maze.h"
#include <ctime>
#include <iostream>
#include "Constants.h"

Maze::Maze(int columns, int rows) {
    this->columns = columns;
    this->rows = rows;

    cells = new Cell* [rows]{};
    for (size_t i{}; i < rows; i++) {
        cells[i] = new Cell[columns]{};
    }

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < columns; x++) {
            cells[x][y] = Cell(x, y);
        }
    }

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < columns; x++) {
            if (x > 0) {
                cells[x][y].AddNeighbour(CellConstants::CELL_LEFT, x-1, y);
            }
            if (x < columns - 1) {
                cells[x][y].AddNeighbour(CellConstants::CELL_RIGHT, x+1, y);
            }
            if (y > 0) {
                cells[x][y].AddNeighbour(CellConstants::CELL_UP, x, y-1);
            }
            if (y < rows - 1) {
                cells[x][y].AddNeighbour(CellConstants::CELL_BOTTOM, x, y+1);
            }
        }
    }
}

Maze::~Maze() {
    for (size_t i = 0; i < rows; i++) {
        delete[] cells[i];
    }
    delete[] cells;
}

Cell* Maze::GetRandomCell() {
    srand((unsigned int)time(NULL));
    int randomX = rand() % columns;
    int randomY = rand() % rows;
    return &(cells[randomX][randomY]);
}

int Maze::GetNumberCells() {
    return rows * columns;
}

void Maze::GenerateMaze() {
    Cell* currentCell = this->GetRandomCell();
    std::map<int, int[2]> neighbours;

    int neighbourY;
    int neighbourX;

    std::vector<std::vector<int>> unvisitedNeighbours;
    std::vector<std::vector<int>> visitedNeighbours;

    srand(time(NULL));
    int randIndex;

    while (currentCell != NULL) {
        neighbours = currentCell->GetAllNeighbours();
        int i = 0;
        for (auto item = neighbours.begin(); item != neighbours.end(); item++) {
            if (this->cells[item->second[0]][item->second[1]].GetNumberLinks() == 0) {
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


            currentCell->link(this->cells[neighbourX][neighbourY]);
            currentCell = &this->cells[neighbourX][neighbourY];
            std::vector<std::vector<int>>().swap(unvisitedNeighbours);
        }
        else {
            currentCell = NULL;
            for (size_t y = 0; y < rows; y++) {
                for (size_t x = 0; x < columns; x++) {

                    if (this->cells[x][y].GetNumberLinks() == 0) {
                        i = 0;
                        neighbours = this->cells[x][y].GetAllNeighbours();
                        for (auto item = neighbours.begin(); item != neighbours.end(); item++) {
                            if (this->cells[item->second[0]][item->second[1]].GetNumberLinks() != 0) {

                                visitedNeighbours.push_back(std::vector<int>());
                                visitedNeighbours[i].push_back(item->second[0]);
                                visitedNeighbours[i].push_back(item->second[1]);
                                i++;
                            }
                        }

                        if (visitedNeighbours.size() > 0) {
                            currentCell = &this->cells[x][y];

                            randIndex = rand() % visitedNeighbours.size();

                            neighbourX = visitedNeighbours[randIndex][0];
                            neighbourY = visitedNeighbours[randIndex][1];

                            currentCell->link(this->cells[neighbourX][neighbourY]);
                            std::vector<std::vector<int>>().swap(visitedNeighbours);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Maze::Load() {

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

            std::vector<std::vector<int>> links = cells[x][y].GetLinks();
            std::map<int, int[2]> allNeighbours = cells[x][y].GetAllNeighbours();

            sf::RectangleShape border;

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
                cells[x][y].BorderUpLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP_LEFT);

                cells[x][y].BorderUpRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP_RIGHT);
                
                cells[x][y].BorderBottomLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM_LEFT);
                
                cells[x][y].BorderBottomRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM_RIGHT);

                xIndex = 0;
                yIndex = 0;
            }
            else if (left == 1 && up == 1 && bottom == 1 && right == 0) {
                cells[x][y].BorderUpLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP_LEFT);

                cells[x][y].BorderBottomLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM_LEFT);

                cells[x][y].BorderRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_RIGHT);

                xIndex = 1;
                yIndex = 0;
            }
            else if (left == 0 && up == 1 && bottom == 1 && right == 1) {
                cells[x][y].BorderUpRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP_RIGHT);

                cells[x][y].BorderBottomRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM_RIGHT);

                cells[x][y].BorderLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_LEFT);

                xIndex = 2;
                yIndex = 0;
            }
            else if (left == 0 && up == 1 && bottom == 1 && right == 0) {
                cells[x][y].BorderLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_LEFT);

                cells[x][y].BorderRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_RIGHT);

                xIndex = 3;
                yIndex = 0;
            }
            else if (left == 1 && up == 1 && bottom == 0 && right == 1) {
                cells[x][y].BorderUpRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP_RIGHT);
                
                cells[x][y].BorderUpLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP_LEFT);

                cells[x][y].BorderBottom(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM);

                xIndex = 0;
                yIndex = 1;
            }
            else if (left == 1 && up == 1 && bottom == 0 && right == 0) {
                cells[x][y].BorderUpLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP_LEFT);

                cells[x][y].BorderBottom(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM);

                cells[x][y].BorderRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_RIGHT);

                xIndex = 1;
                yIndex = 1;
            }
            else if (left == 0 && up == 1 && bottom == 0 && right == 1) {
                cells[x][y].BorderUpRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP_RIGHT);

                cells[x][y].BorderLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_LEFT);

                cells[x][y].BorderBottom(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM);

                xIndex = 2;
                yIndex = 1;
            }
            else if (left == 0 && up == 1 && bottom == 0 && right == 0) {
                cells[x][y].BorderRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_RIGHT);

                cells[x][y].BorderLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_LEFT);

                cells[x][y].BorderBottom(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM);

                xIndex = 3;
                yIndex = 1;
            }
            else if (left == 1 && up == 0 && bottom == 1 && right == 1) {

                cells[x][y].BorderUp(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP);

                cells[x][y].BorderBottomLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM_LEFT);

                cells[x][y].BorderBottomRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM_RIGHT);

                xIndex = 0;
                yIndex = 2;
            }
            else if (left == 1 && up == 0 && bottom == 1 && right == 0) {
                
                cells[x][y].BorderUp(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP);

                cells[x][y].BorderBottomLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM_LEFT);

                cells[x][y].BorderRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_RIGHT);

                xIndex = 1;
                yIndex = 2;
            }
            else if (left == 0 && up == 0 && bottom == 1 && right == 1) {
                
                cells[x][y].BorderUp(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP);

                cells[x][y].BorderBottomRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM_RIGHT);

                cells[x][y].BorderLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_LEFT);

                xIndex = 2;
                yIndex = 2;
            }
            else if (left == 0 && up == 0 && bottom == 1 && right == 0) {
                cells[x][y].BorderUp(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP);

                cells[x][y].BorderLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_LEFT);

                cells[x][y].BorderRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_RIGHT);
                
                xIndex = 3;
                yIndex = 2;
            }
            else if (left == 1 && up == 0 && bottom == 0 && right == 1) {
                cells[x][y].BorderUp(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP);

                cells[x][y].BorderBottom(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM);

                xIndex = 0;
                yIndex = 3;
            }
            else if (left == 1 && up == 0 && bottom == 0 && right == 0) {
                cells[x][y].BorderUp(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP);

                cells[x][y].BorderBottom(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM);

                cells[x][y].BorderRight(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_RIGHT);

                xIndex = 1;
                yIndex = 3;
            }
            else if (left == 0 && up == 0 && bottom == 0 && right == 1) {
                cells[x][y].BorderUp(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_UP);

                cells[x][y].BorderBottom(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_BOTTOM);

                cells[x][y].BorderLeft(cellTextureWight, cellTextureHeight, BorderConstants::BORDER_LEFT);
                xIndex = 2;
                yIndex = 3;
            }

            cells[x][y].GetSprite().setTexture(cellTexture);
            cells[x][y].GetSprite().setTextureRect(sf::IntRect((cellTextureHeight + distanceBetweenTexture) * xIndex, (cellTextureHeight + distanceBetweenTexture) * yIndex, cellTextureWight, cellTextureHeight));
            cells[x][y].GetSprite().setPosition(x * cellTextureWight, y * cellTextureHeight);
        }
    }
}

void Maze::Update() {
}

void Maze::Draw(sf::RenderWindow& window) {
    for (size_t y = 0; y < rows; y++)
    {
        for (size_t x = 0; x < columns; x++)
        {
            for (auto item = cells[x][y].borders.begin(); item != cells[x][y].borders.end(); item++) {
                window.draw(cells[x][y].borders[item->first]);
            }
            window.draw(cells[x][y].GetSprite());
        }
    }
}

