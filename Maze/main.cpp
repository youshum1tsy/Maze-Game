#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"
#include "Maze.h"
#include "Cell.h"
#include "Math.h"

const int BORDER_BOTTOM = 1;
const int BORDER_BOTTOM_RIGHT = 2;
const int BORDER_BOTTOM_LEFT = 3;
const int BORDER_UP = 4;
const int BORDER_UP_LEFT = 5;
const int BORDER_UP_RIGHT = 6;
const int BORDER_LEFT = 7;
const int BORDER_RIGHT = 8;

int main() {
    int columns = 20;
    int rows = 20;

    Maze map(columns, rows);
    map.GenerateMaze();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Maze-Game");

    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    float playerSpeed = 0.5f;

    playerSprite.setPosition(sf::Vector2f(48, 48));

    float cameraSizeX = 1920;
    float cameraSizeY = 1080;
    sf::View playerCamera(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y), sf::Vector2f(cameraSizeX, cameraSizeY));
    
    window.setView(playerCamera);

    map.Load();

    if (playerTexture.loadFromFile("../Assets/Player/stylesheet.png")) {
        std::cout << "player texture successful loaded";
        playerSprite.setTexture(playerTexture);
        playerSprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
    }
    else {
        std::cout << "player texture successful loaded";
    }

    int cellX;
    int cellY;
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        cellX = std::floor(playerSprite.getPosition().x / 96);
        cellY = std::floor(playerSprite.getPosition().y / 96);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (!(DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_LEFT].getGlobalBounds()))) {
                playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y - playerSpeed));
                playerCamera.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);
            }
            else {
                std::cout << "colision" << std::endl;
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (!(DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_LEFT].getGlobalBounds()) || 
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_LEFT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_LEFT].getGlobalBounds()))) {
                playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x - playerSpeed, playerSprite.getPosition().y));
                playerCamera.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);
            }
            else {
                std::cout << "colision" << std::endl;
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (!(DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_RIGHT].getGlobalBounds()))) {

                playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x + playerSpeed, playerSprite.getPosition().y));
                playerCamera.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);
            }
            else {
                std::cout << "colision" << std::endl;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (!(DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_LEFT].getGlobalBounds()))) {
                playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y + playerSpeed));
                playerCamera.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);
            }
            else {
                std::cout << "colision" << std::endl;
            }

        }

       if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (!(DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_LEFT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_LEFT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP].getGlobalBounds()) || 
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_LEFT].getGlobalBounds()))) {
                playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x - playerSpeed, playerSprite.getPosition().y - playerSpeed));
                playerCamera.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);
            }
            else {
                std::cout << "colision" << std::endl;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (!(DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_LEFT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_LEFT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_RIGHT].getGlobalBounds()))) {

                playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x + playerSpeed, playerSprite.getPosition().y - playerSpeed));
                playerCamera.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);
            }
            else {
                std::cout << "colision" << std::endl;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (!(DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_LEFT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_LEFT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_RIGHT].getGlobalBounds()))) {

                playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x + playerSpeed, playerSprite.getPosition().y + playerSpeed));
                playerCamera.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);
            }
            else {
                std::cout << "colision" << std::endl;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (!(DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_LEFT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_UP_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_LEFT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM_RIGHT].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_BOTTOM].getGlobalBounds()) ||
                DidRectCollision(playerSprite.getGlobalBounds(), map.cells[cellX][cellY].borders[BORDER_LEFT].getGlobalBounds()))) {

                playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x - playerSpeed, playerSprite.getPosition().y + playerSpeed));
                playerCamera.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);
            }
            else {
                std::cout << "colision" << std::endl;
            }
        }
        
        window.clear(sf::Color::Black);
        map.Draw(window);
        window.draw(playerSprite);

        window.setView(playerCamera);
        window.display();
    }

    return 0;
}