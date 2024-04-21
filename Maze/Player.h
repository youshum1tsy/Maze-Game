#pragma once
#include <SFML/Graphics.hpp>
#include "Maze.h"

class Player {
public:
	void Initialize();
	void Load();
	void Update(Cell** cells, Cell startCell, Cell endCell, float deltaTime);
	void Draw(sf::RenderWindow& window);

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::View camera;
	int cameraWidth;
	int cameraHeight;
	float playerSpeed;
};

