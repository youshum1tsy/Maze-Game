#pragma once
#include "Cell.h"
class Maze{
public:
	Maze(int columns, int rows);
	~Maze();
	void GenerateMaze();

	void Load();
	void Update();
	void Draw(sf::RenderWindow& window);
	
	Cell* GetRandomCell();
	int GetNumberCells();

	Cell** cells;

private:
	const int CELL_BOTTOM = 1;
	const int CELL_RIGHT = 2;
	const int CELL_UP = 3;
	const int CELL_LEFT = 4;

	const int BORDER_BOTTOM = 1;
	const int BORDER_BOTTOM_RIGHT = 2;
	const int BORDER_BOTTOM_LEFT = 3;
	const int BORDER_UP = 4;
	const int BORDER_UP_LEFT = 5;
	const int BORDER_UP_RIGHT = 6;
	const int BORDER_LEFT = 7;
	const int BORDER_RIGHT = 8;

	sf::Texture cellTexture;
	int columns = 4;
	int rows = 4;
};

