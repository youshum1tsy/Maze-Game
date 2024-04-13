#pragma once
#include "Cell.h"
class Maze{
public:
	Maze(int columns, int rows);
	~Maze();

	Cell* GetRandomCell();
	int GetNumberCells();


	Cell** cells;
private:
	int columns = 4;
	int rows = 4;
};

