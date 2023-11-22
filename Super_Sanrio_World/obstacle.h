#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "position.h"

using namespace sf;

class Obstacle : Position {
public:
    Obstacle();

    // ��ֹ� ���� getter
    int getObstacleCnt();

    // Sprite getter
    Sprite getSprites(int);

    // ��ֹ� ��ġ (x, y) getter
    int getObstaclePosX(int);
    int getObstaclePosY(int);

    void setObstaclePosX(int, int);
    void setObstaclePosY(int, int);

    void moveObatacle();

    int getObstacleSpeed();
    void setObstacleSpeed(int);
    void sumSpeed(int);

private:
    static const int obstacleCnt = 3;
    float obstacleSpeed = 7;
    int obstaclePosition;
    Texture obstacle[obstacleCnt];
    Position obstaclePos[obstacleCnt];
    Sprite obstacleSprite[obstacleCnt];
};