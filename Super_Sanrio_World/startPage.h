#pragma once
#include <SFML/Graphics.hpp>

class startPage {
public:
    startPage(const std::string startPagePath);
    void draw(sf::RenderWindow& window) const;

private:
    sf::Texture startPageTexture;
    sf::Sprite startSprite;
};
