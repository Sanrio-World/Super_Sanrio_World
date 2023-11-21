#pragma once
#include <SFML/Graphics.hpp>

class endPage {
public:
    endPage(const std::string endPagePath);
    void draw(sf::RenderWindow& window) const;

private:
    sf::Texture endPageTexture;
    sf::Sprite endPageSprite;
};
