#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class Cell{
public:
	Cell();
	Cell(int x, int y);

	void AddNeighbour(int direction, int x, int y);
	std::map<int, int[2]> GetAllNeighbours();
	
	std::vector<std::vector<int>> GetLinks();
	size_t GetNumberLinks();
	void link(Cell& cell);

	int GetX();
	int GetY();

	void SetX(int x);
	void SetY(int y);

	sf::Sprite& GetSprite();
	
	void BorderUpLeft(int cellTextureWight, int cellTextureHeight, int direction);
	void BorderUpRight(int cellTextureWight, int cellTextureHeight, int direction);
	void BorderUp(int cellTextureWight, int cellTextureHeight, int direction);
	void BorderBottomLeft(int cellTextureWight, int cellTextureHeight, int direction);
	void BorderBottomRight(int cellTextureWight, int cellTextureHeight, int direction);
	void BorderBottom(int cellTextureWight, int cellTextureHeight, int direction);
	void BorderLeft(int cellTextureWight, int cellTextureHeight, int direction);
	void BorderRight(int cellTextureWight, int cellTextureHeight, int direction);

	std::vector<std::vector<int>> links;
	std::map<int ,sf::RectangleShape> borders;

private:
	std::map<int, int[2]> neighboursCords;
	std::vector<int> directions;

	int x;
	int y;

	sf::Sprite sprite;
};

