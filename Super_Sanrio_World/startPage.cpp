#include "startPage.h"

startPage::startPage(const std::string startPagePath) {
    startPageTexture.loadFromFile(startPagePath);
    startSprite.setTexture(startPageTexture);
    startSprite.setTextureRect(sf::IntRect(0, 0, 840, 480));
}

void startPage::draw(sf::RenderWindow& window) const {
    window.clear();
    window.draw(startSprite);
}
