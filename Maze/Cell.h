#pragma once
#include <vector>
#include <map>

class Cell{
public:
	Cell();
	Cell(int x, int y);

	void AddNeighbour(int direction, int x, int y);
	//Cell* GetNeighbour(int direction);

	//Cell GetRandomNeighbour();

	std::map<int, int[2]> GetAllNeighbours();

	size_t GetNumberLinks();
	void link(Cell& cell);

	int GetX();
	int GetY();

	std::vector<int> directions;
	std::map<int, int[2]> neighboursCords;
	std::vector<Cell> links;
private:
	int x;
	int y;
};

