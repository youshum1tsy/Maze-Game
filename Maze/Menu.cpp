#include "Menu.h"
#include <iostream>
#include "Constants.h"

void Menu::Initialize() {
	isMenu = 1;
	menuNum = MenuConstants::MAIN;
}

void Menu::Load() {
	backgroundTexture.loadFromFile("../Assets/Menu/main_menu.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);
	
	playTexture.loadFromFile("../Assets/Menu/play.png");
	quitTexture.loadFromFile("../Assets/Menu/quit.png");

	playSprite.setTexture(playTexture);
	quitSprite.setTexture(quitTexture);

	playSprite.setTextureRect(sf::IntRect(0, 0, 272, 80));
	quitSprite.setTextureRect(sf::IntRect(0, 0, 272, 80));

	playSprite.setPosition(960 - 272 / 2, 590);
	quitSprite.setPosition(960 - 272 / 2, 700);
}

void Menu::Update(sf::RenderWindow& window) {
	playSprite.setTextureRect(sf::IntRect(0, 0, 272, 80));
	quitSprite.setTextureRect(sf::IntRect(0, 0, 272, 80));

	if (sf::IntRect(960 - 272 / 2, 590, 272, 80).contains(sf::Mouse::getPosition(window))) {
		playSprite.setTextureRect(sf::IntRect(272 + 2, 0, 272, 80));
		menuNum = MenuConstants::PLAY;
	}
	if (sf::IntRect(960 - 272 / 2, 700, 272, 80).contains(sf::Mouse::getPosition(window))) {
		quitSprite.setTextureRect(sf::IntRect(272 + 2, 0, 272, 80));
		menuNum = MenuConstants::QUIT;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (menuNum == MenuConstants::PLAY && sf::IntRect(960 - 272 / 2, 590, 272, 80).contains(sf::Mouse::getPosition(window))) {
			isMenu = false;
		}
		if (menuNum == MenuConstants::QUIT && sf::IntRect(960 - 272 / 2, 700, 272, 80).contains(sf::Mouse::getPosition(window))) {
			window.close();
			isMenu = false;
		}
	}
}

void Menu::Draw(sf::RenderWindow& window) {
	window.draw(backgroundSprite);
	window.draw(playSprite);
	window.draw(quitSprite);
	window.display();
}

bool Menu::GetIsMenu() {
	return isMenu;
}
