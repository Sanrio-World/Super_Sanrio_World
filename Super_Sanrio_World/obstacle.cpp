#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "position.h"
#include "obstacle.h"

#define WIDTH 840
#define HEIGHT 480

Obstacle::Obstacle() {
    obstacle[0].loadFromFile("resources/obstacle1.png");
    obstacle[1].loadFromFile("resources/obstacle2.png");
    obstacle[2].loadFromFile("resources/obstacle4.png");

    srand(time(nullptr)); // 랜덤 시드 초기화
    obstaclePosition = rand() % 920 + 780;

    for (int i = 0; i < obstacleCnt; i++) {
        obstaclePos[i].x = obstaclePosition + (i * 310);
        obstaclePos[i].y = 350;
        obstacleSprite[i].setPosition(obstaclePos[i].x, obstaclePos[i].y);
        obstacleSprite[i].setTexture(obstacle[i]);
    }
}

// 장애물 개수 getter
int Obstacle::getObstacleCnt() { return obstacleCnt; }

// Sprite getter
Sprite Obstacle::getSprites(int i) { return obstacleSprite[i]; }

// 장애물 위치 (x, y) getter
int Obstacle::getObstaclePosX(int i) { return obstaclePos[i].x; }
int Obstacle::getObstaclePosY(int i) { return obstaclePos[i].y; }

void Obstacle::setObstaclePosX(int i, int pos) { obstaclePos[i].x = pos; }
void Obstacle::setObstaclePosY(int i, int pos) { obstaclePos[i].y = pos; }

void Obstacle::moveObatacle() {
    srand(time(nullptr)); // 랜덤 시드 초기화
    int distance = rand() % 330 + 310;
    for (int i = 0; i < obstacleCnt; i++) {
        if (obstaclePos[i].x <= -30)
        {
            //obstacleSpeed = rand() % 2 + (obstacleSpeed - 1);
            obstaclePos[i].x = WIDTH + (i * distance);
        }
        else
        {
            obstaclePos[i].x -= obstacleSpeed;
        }
        obstacleSprite[i].setPosition(obstaclePos[i].x, obstaclePos[i].y);
    }
}

int Obstacle::getObstacleSpeed() { return obstacleSpeed; }
void Obstacle::setObstacleSpeed(int num) { obstacleSpeed = num; }
void Obstacle::sumSpeed(int sum) {
    obstacleSpeed += sum;
}