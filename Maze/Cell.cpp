#include <ctime>
#include "Cell.h"

Cell::Cell() {
}

Cell::Cell(int x, int y) {
	this->x = x;
	this->y = y;
}

void Cell::AddNeighbour(int direction, int x, int y) {
	this->directions.push_back(direction);
	this->neighboursCords[direction][0] = x;
	this->neighboursCords[direction][1] = y;
}

 std::map<int, int[2]> Cell::GetAllNeighbours() {
	 return neighboursCords;
}

void Cell::link(Cell& cell) {
	links.push_back(std::vector<int>());
	this->links[links.size() - 1].push_back(cell.GetX());
	this->links[links.size() - 1].push_back(cell.GetY());

	cell.links.push_back(std::vector<int>());
	cell.links[cell.links.size() - 1].push_back(this->GetX());
	cell.links[cell.links.size() - 1].push_back(this->GetY());
}

std::vector<std::vector<int>> Cell::GetLinks() {
	return links;
}

size_t Cell::GetNumberLinks() {
	return links.size();
}

int Cell::GetX() {
	return x;
}
int Cell::GetY() {
	return y;
}

void Cell::SetX(int x) {
	this->x = x;
}

void Cell::SetY(int y) {
	this->y = y;
}

sf::Sprite& Cell::GetSprite() {
	return sprite;
}

void Cell::BorderUpLeft(int cellTextureWight, int cellTextureHeight, int direction) {
	sf::RectangleShape border;
	border.setSize(sf::Vector2f(16, 32));
	border.setPosition(sf::Vector2f(x * cellTextureWight, y * cellTextureHeight));
	borders.insert(std::make_pair(direction, border));
}

void Cell::BorderUpRight(int cellTextureWight, int cellTextureHeight, int direction) {
	sf::RectangleShape border;
	border.setSize(sf::Vector2f(16, 32));
	border.setPosition(sf::Vector2f(x * cellTextureWight + (cellTextureWight - 16), y * cellTextureHeight));
	borders.insert(std::make_pair(direction, border));
}

void Cell::BorderUp(int cellTextureWight, int cellTextureHeight, int direction) {
	sf::RectangleShape border;
	border.setSize(sf::Vector2f(96, 32));
	border.setPosition(sf::Vector2f(x * cellTextureWight, y * cellTextureHeight));
	borders.insert(std::make_pair(direction, border));
}

void Cell::BorderBottomLeft(int cellTextureWight, int cellTextureHeight, int direction) {
	sf::RectangleShape border;
	border.setSize(sf::Vector2f(16, 16));
	border.setPosition(sf::Vector2f(x * cellTextureWight, y * cellTextureHeight + (cellTextureHeight - 16)));
	borders.insert(std::make_pair(direction, border));
}

void Cell::BorderBottomRight(int cellTextureWight, int cellTextureHeight, int direction) {
	sf::RectangleShape border;
	border.setSize(sf::Vector2f(16, 16));
	border.setPosition(sf::Vector2f(x * cellTextureWight + (cellTextureWight - 16), y * cellTextureHeight + (cellTextureHeight - 16)));
	borders.insert(std::make_pair(direction, border));
}

void Cell::BorderBottom(int cellTextureWight, int cellTextureHeight, int direction) {
	sf::RectangleShape border;
	border.setSize(sf::Vector2f(96, 16));
	border.setPosition(sf::Vector2f(x * cellTextureWight, y * cellTextureHeight + (cellTextureHeight - 16)));
	borders.insert(std::make_pair(direction, border));
}

void Cell::BorderLeft(int cellTextureWight, int cellTextureHeight, int direction) {
	sf::RectangleShape border;
	border.setSize(sf::Vector2f(16, 96));
	border.setPosition(sf::Vector2f(x * cellTextureWight, y * cellTextureHeight));
	borders.insert(std::make_pair(direction, border));
}

void Cell::BorderRight(int cellTextureWight, int cellTextureHeight, int direction) {
	sf::RectangleShape border;
	border.setSize(sf::Vector2f(16, 96));
	border.setPosition(sf::Vector2f(x * cellTextureWight + (cellTextureWight - 16), y * cellTextureHeight));
	borders.insert(std::make_pair(direction, border));
}
