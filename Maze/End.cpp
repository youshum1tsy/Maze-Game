#include <iostream>
#include <fstream>
#include "End.h"
#include "Start.h"
#include "Constants.h"

void End::Initialize() {
	isMenu = 1;
	menuNum = EndConstants::RESULT;
}

void End::Load() {
	backgroundTexture.loadFromFile("../Assets/End/end_menu.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);

	quitTexture.loadFromFile("../Assets/End/quit.png");
	tryAgainTexture.loadFromFile("../Assets/End/try-again.png");

	quitSprite.setTexture(quitTexture);
	tryAgainSprite.setTexture(tryAgainTexture);

	quitSprite.setTextureRect(sf::IntRect(0, 0, 272, 80));
	tryAgainSprite.setTextureRect(sf::IntRect(0, 0, 592, 80));

	quitSprite.setPosition(960 - 272 / 2, 700);
	tryAgainSprite.setPosition(960 - 592 / 2, 600);

	Font.loadFromFile("../Assets/Timer/font.ttf");

	timerText.setFont(Font);
	timerText.setCharacterSize(48);
	timerText.setFillColor(sf::Color::Red);
	timerText.setPosition(600, 150);

	scoreText.setFont(Font);
	scoreText.setCharacterSize(32);
	scoreText.setFillColor(sf::Color::Black);	
}

void End::Update(sf::RenderWindow& window) {
	quitSprite.setTextureRect(sf::IntRect(0, 0, 272, 80));
	tryAgainSprite.setTextureRect(sf::IntRect(0, 0, 592, 80));

	std::string line;

	std::string lastTimePath = "../Scores/lastTime.txt";
	std::ifstream inLastTimeFile(lastTimePath);
	std::getline(inLastTimeFile, line);

	timerText.setString("Your time: " + line + " seconds");
	inLastTimeFile.close();

	score.clear();
	std::string scorePath = "../Scores/score.txt";
	std::ifstream scoreFile(scorePath);
	while (std::getline(scoreFile, line)) {
		score.push_back(line); 
	}

	if (sf::IntRect(960 - 592 / 2, 600, 592, 80).contains(sf::Mouse::getPosition(window))) {
		tryAgainSprite.setTextureRect(sf::IntRect(592 + 1, 0, 592, 80));
		menuNum = EndConstants::TRYAGAIN;
	}
	if (sf::IntRect(960 - 272 / 2, 700, 272, 80).contains(sf::Mouse::getPosition(window))) {
		quitSprite.setTextureRect(sf::IntRect(272 + 2, 0, 272, 80));
		menuNum = EndConstants::QUIT;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (menuNum == EndConstants::TRYAGAIN && sf::IntRect(960 - 592 / 2, 600, 592, 80).contains(sf::Mouse::getPosition(window))) {
			startgame(window);
		}
		if (menuNum == EndConstants::QUIT && sf::IntRect(960 - 272 / 2, 700, 272, 80).contains(sf::Mouse::getPosition(window))) {
			window.close();
			isMenu = false;
		}
	}
}

void End::Draw(sf::RenderWindow& window) {
	window.clear(sf::Color::Black);
	window.draw(backgroundSprite);
	window.draw(quitSprite);
	window.draw(tryAgainSprite);
	window.draw(timerText);
	size_t i = 0;
	for (std::string time : score) {
		i++;
		scoreText.setString("top " + std::to_string(i) + ": " + time + " sec");
		scoreText.setPosition(800, 200 + i * 32);
		if (i == 11) {
			break;
		}
		window.draw(scoreText);
	}
	window.display();
}

bool End::GetIsMenu() {
	return isMenu;
}
