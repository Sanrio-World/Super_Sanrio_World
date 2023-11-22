#include<SFML/Graphics.hpp>
#include <iostream>
#include "scoreText.h"

ScoreText::ScoreText(Font& font, int size, int x, int y, Color color) 
    : font(font), size(size), x(x), y(y), textColor(color) {
    printText.setFont(font);
    printText.setCharacterSize(size);
    printText.setFillColor(color); 
    printText.setPosition(x, y);
}
    
void ScoreText::setString(int score) {
    printText.setString(std::to_string(score));
}

void ScoreText::draw(RenderWindow& window) {
    window.draw(printText);
}
