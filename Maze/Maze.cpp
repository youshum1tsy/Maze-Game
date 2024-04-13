#include "Maze.h"
#include <ctime>
#include <iostream>

const int CELL_BOTTOM = 1;
const int CELL_RIGHT = 2;
const int CELL_UP = 3;
const int CELL_LEFT = 4;

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
                cells[x][y].AddNeighbour(CELL_LEFT, x-1, y);
            }
            if (x < columns - 1) {
                cells[x][y].AddNeighbour(CELL_RIGHT, x+1, y);
            }
            if (y > 0) {
                cells[x][y].AddNeighbour(CELL_UP, x, y-1);
            }
            if (y < rows - 1) {
                cells[x][y].AddNeighbour(CELL_BOTTOM, x, y+1);
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
