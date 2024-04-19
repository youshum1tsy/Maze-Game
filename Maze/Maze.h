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

	sf::Texture cellTexture;
	int columns = 4;
	int rows = 4;
};

