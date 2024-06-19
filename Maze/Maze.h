#pragma once
#include "Cell.h"
class Maze{
public:
	Maze(int columns, int rows);
	~Maze();
	void GenerateMaze();
	void GenerateStartRoom();
	void GenerateEndRoom();

	void Load();
	void Draw(sf::RenderWindow& window);
	
	Cell* GetRandomCell();
	int GetNumberCells();

	Cell** cells;

	Cell startCell;
	Cell endCell;

private:
	sf::Texture cellTexture;
	int cellTextureHeight = 96;
	int cellTextureWight = 96;
	int distanceBetweenTexture = 32;
	int columns;
	int rows;
};

