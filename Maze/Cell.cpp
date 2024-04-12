#include "Cell.h"
#include <iterator>
#include <iterator>
#include <ctime>

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
	this->links.push_back(cell);
	cell.links.push_back(*this);
}

size_t Cell::GetNumberLinks()
{
	return links.size();
}

int Cell::GetX()
{
	return x;
}
int Cell::GetY()
{
	return y;
}
