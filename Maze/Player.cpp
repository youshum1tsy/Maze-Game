#include <iostream>
#include "Player.h"
#include "Math.h"
#include "Constants.h"

void Player::Initialize() {
	playerSpeed = 0.25;
    sprite.setPosition(sf::Vector2f(0, 0));
    int cameraWidth = 1920;
    int cameraHeight = 1080;
    camera.setCenter(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
    camera.setSize(cameraWidth, cameraHeight);
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
}

void Player::Update(Cell** cells, Cell startCell, Cell endCell, float deltaTime) {

    int x = std::floor(sprite.getPosition().x / 96);
    int y = std::floor(sprite.getPosition().y / 96);
    sf::Vector2f position = sprite.getPosition();

    if (x == startCell.GetSprite().getPosition().x / 96 && y == startCell.GetSprite().getPosition().y / 96) {
        std::cout << "start" << std::endl;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_UP].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_UP_LEFT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(0, -1) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "UP colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_BOTTOM].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_BOTTOM_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_BOTTOM_LEFT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(0, 1) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "DOWN colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_LEFT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_UP_LEFT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_BOTTOM_LEFT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(-1, 0) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "LEFT colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), startCell.borders[BorderConstants::BORDER_BOTTOM_RIGHT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(1, 0) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "RIGHT colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }
        }
    }
    else if (x == endCell.GetSprite().getPosition().x / 96 && y == endCell.GetSprite().getPosition().y / 96) {
        std::cout << "end" << std::endl;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_UP].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_UP_LEFT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(0, -1) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "UP colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_BOTTOM].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_BOTTOM_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_BOTTOM_LEFT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(0, 1) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "DOWN colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_LEFT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_UP_LEFT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_BOTTOM_LEFT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(-1, 0) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "LEFT colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), endCell.borders[BorderConstants::BORDER_BOTTOM_RIGHT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(1, 0) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "RIGHT colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_UP].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_UP_LEFT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(0, -1) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "UP colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_BOTTOM].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_BOTTOM_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_BOTTOM_LEFT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(0, 1) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "DOWN colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_LEFT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_UP_LEFT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_BOTTOM_LEFT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(-1, 0) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "LEFT colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (!(DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(sprite.getGlobalBounds(), cells[x][y].borders[BorderConstants::BORDER_BOTTOM_RIGHT].getGlobalBounds()))) {
                sprite.setPosition(sf::Vector2f(position + sf::Vector2f(1, 0) * playerSpeed * deltaTime));
                camera.setCenter((int)sprite.getPosition().x, (int)sprite.getPosition().y);
            }
            else {
                sprite.setPosition(position);
                std::cout << "RIGHT colision " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
            }
        }
    }
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.setView(camera);
}

