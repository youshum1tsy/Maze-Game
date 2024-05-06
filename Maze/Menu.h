#pragma once
#include <SFML/Graphics.hpp>
class Menu {
public:
    
    void Initialize();
    void Load();
    void Update(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    
    bool GetIsMenu();

private:
    sf::Texture backgroundTexture;
    sf::Texture playTexture;
    sf::Texture quitTexture;

    sf::Sprite backgroundSprite;
    sf::Sprite playSprite;
    sf::Sprite quitSprite;

    bool isMenu;
    int menuNum;
};

