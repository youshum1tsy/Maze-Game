#include <iostream>
#include "Player.h"
#include "Math.h"
#include "Constants.h"

void Player::Initialize(int columns, int rows) {
	playerSpeed = 0.25;
    sprite.setPosition(sf::Vector2f(96 * columns / 2 - 12, 96 * rows + 96 / 2));
    cameraWidth = 1920;
    cameraHeight = 1080;
    camera.setCenter(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
    camera.setSize(cameraWidth, cameraHeight);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Red);

}

void Player::Load() {
    if (texture.loadFromFile("../Assets/Player/stylesheet.png")) {
        std::cout << "player texture successful loaded";
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
    }
    else {
        std::cout << "player texture error when loaded";
    }
    timerFont.loadFromFile("../Assets/Timer/font.ttf");
    timerText.setFont(timerFont);
}

void Player::Update(Cell** cells, Cell startCell, Cell endCell, float deltaTime) {

    int x = std::floor(sprite.getPosition().x / 96);
    int y = std::floor(sprite.getPosition().y / 96);
    sf::Vector2f position = sprite.getPosition();

    if (x == startCell.GetSprite().getPosition().x / 96 && y == startCell.GetSprite().getPosition().y / 96) {
        moveUp(startCell, deltaTime, position);
        
        moveDown(startCell, deltaTime, position);

        moveLeft(startCell, deltaTime, position);
        
        moveRight(startCell, deltaTime, position);
    }
    else if (x == endCell.GetSprite().getPosition().x / 96 && y == endCell.GetSprite().getPosition().y / 96) {
        moveUp(endCell, deltaTime, position);
        
        moveDown(endCell, deltaTime, position);

        moveLeft(endCell, deltaTime, position);
       
        moveRight(endCell, deltaTime, position);
    }
    else {
        moveUp(cells[x][y], deltaTime, position);
        
        moveDown(cells[x][y], deltaTime, position);
        
        moveLeft(cells[x][y], deltaTime, position);

        moveRight(cells[x][y], deltaTime, position);

    }
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.setView(camera);
    timerText.setPosition(camera.getCenter().x - cameraWidth / 2, camera.getCenter().y - cameraHeight / 2);

    timerText.setString(std::to_string(timer.getElapsedTime().asSeconds()));
    window.draw(timerText);
}

void Player::moveUp(Cell Cell, float deltaTime, sf::Vector2f position) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (!(DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_UP].getGlobalBounds()) ||
            DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_UP_RIGHT].getGlobalBounds()) ||
            DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_UP_LEFT].getGlobalBounds()))) {
            sprite.setPosition(sf::Vector2f(position + sf::Vector2f(0, -1) * playerSpeed * deltaTime));
            camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
        }
        else {
            sprite.setPosition(position);
        }
    }
}

void Player::moveRight(Cell Cell, float deltaTime, sf::Vector2f position) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (!(DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_RIGHT].getGlobalBounds()) ||
            DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_UP_RIGHT].getGlobalBounds()) ||
            DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_BOTTOM_RIGHT].getGlobalBounds()))) {
            sprite.setPosition(sf::Vector2f(position + sf::Vector2f(1, 0) * playerSpeed * deltaTime));
            camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
        }
        else {
            sprite.setPosition(position);
        }
    }
}

void Player::moveDown(Cell Cell, float deltaTime, sf::Vector2f position) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (!(DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_BOTTOM].getGlobalBounds()) ||
            DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_BOTTOM_RIGHT].getGlobalBounds()) ||
            DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_BOTTOM_LEFT].getGlobalBounds()))) {
            sprite.setPosition(sf::Vector2f(position + sf::Vector2f(0, 1) * playerSpeed * deltaTime));
            camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
        }
        else {
            sprite.setPosition(position);
        }
    }
}

void Player::moveLeft(Cell Cell, float deltaTime, sf::Vector2f position) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (!(DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_LEFT].getGlobalBounds()) ||
            DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_UP_LEFT].getGlobalBounds()) ||
            DidRectCollision(sprite.getGlobalBounds(), Cell.borders[BorderConstants::BORDER_BOTTOM_LEFT].getGlobalBounds()))) {
            sprite.setPosition(sf::Vector2f(position + sf::Vector2f(-1, 0) * playerSpeed * deltaTime));
            camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
        }
        else {
            sprite.setPosition(position);
        }
    }
}