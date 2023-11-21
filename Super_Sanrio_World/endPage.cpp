#include "endPage.h"
using namespace sf;

endPage::endPage(const std::string endPagePath) {
    endPageTexture.loadFromFile(endPagePath);
    endPageSprite.setTexture(endPageTexture);
    endPageSprite.setTextureRect(sf::IntRect(0, 0, 840, 480));
}


void endPage::draw(sf::RenderWindow& window) const {
    window.clear();
    window.draw(endPageSprite);
}
