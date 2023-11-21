#include "currentPage.h"
#include "SFML/Graphics.hpp"
#include "startPage.cpp"
#include "gamePage.cpp"
#include "endPage.cpp"

enum CurrentP {
    StartP,
    GameP,
    EndP
};

class CurrentPageManager {
private:
    startPage startP;
    gamePage gameP;
    endPage endP;
    CurrentP currentPage;

public:
    CurrentPageManager() : currentPage(CurrentP::StartP) {}

    void handleEvents(sf::RenderWindow& window) {
        switch (currentPage) {
        case CurrentP::StartP:
            startP.handleEvents(window, currentPage);
            break;
        case CurrentP::GameP:
            gameP.handleEvents(window, currentPage);
            break;
        case CurrentP::EndP:
            endP.handleEvents(window, currentPage);
            break;
        }
    }

    void draw(sf::RenderWindow& window) {
        switch (currentPage) {
        case CurrentP::StartP:
            startP.draw(window);
            break;
        case CurrentP::GameP:
            gameP.draw(window);
            break;
        case CurrentP::EndP:
            endP.draw(window);
            break;
        }
    }
};
