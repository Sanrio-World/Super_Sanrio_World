#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "position.h"

#define WIDTH 840
#define HEIGHT 480

using namespace sf;

class Cloud {
public:
    Cloud();

    int getCloudCnt();

    void drawCloud(RenderWindow&);

    void moveCloud();

private:
    static const int cloudCnt = 5;
    Texture cloud[cloudCnt];
    Position cloudPos[cloudCnt];
    Sprite cloudSprite[cloudCnt];
};