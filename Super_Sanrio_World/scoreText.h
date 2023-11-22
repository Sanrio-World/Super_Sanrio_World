#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;

class ScoreText {
public:
    ScoreText(Font& font, int size, int x, int y, Color color);
    void setString(int score);
    void draw(RenderWindow& window);
private:
    Text printText;
    int x;
    int y;
    int size;
    Font& font;
    Color textColor;
};
