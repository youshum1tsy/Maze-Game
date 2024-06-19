#pragma once
#include <SFML/Graphics.hpp>
class End{
public:

    void Initialize();
    void Load();
    void Update(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    bool GetIsMenu();

private:
    sf::Texture backgroundTexture;
    sf::Texture tryAgainTexture;
    sf::Texture quitTexture;

    sf::Sprite backgroundSprite;
    sf::Sprite tryAgainSprite;
    sf::Sprite quitSprite;

    sf::Text timerText;
    sf::Font Font;

    std::vector<std::string> score;
    sf::Text scoreText;

    bool isMenu;
    int menuNum;
};