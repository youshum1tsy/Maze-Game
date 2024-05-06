#pragma once
#include <SFML/Graphics.hpp>
#include "Maze.h"

class Player {
public:
	void Initialize(int columns, int rows);
	void Load();
	void Update(Cell** cells, Cell startCell, Cell endCell, float deltaTime);
	void Draw(sf::RenderWindow& window);

private:

	void moveUp(Cell Cell, float deltaTime, sf::Vector2f position);
	void moveRight(Cell Cell, float deltaTime, sf::Vector2f position);
	void moveDown(Cell Cell, float deltaTime, sf::Vector2f position);
	void moveLeft(Cell Cell, float deltaTime, sf::Vector2f position);

	sf::Texture texture;
	sf::Sprite sprite;
	sf::View camera;
	int cameraWidth;
	int cameraHeight;
	float playerSpeed;

	sf::Clock timer;
	sf::Text timerText;
	sf::Font timerFont;
	sf::Vector2f timerPosition;
};

