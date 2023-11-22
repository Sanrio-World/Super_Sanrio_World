#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "cloud.h"
#include "position.h"

#define WIDTH 840
#define HEIGHT 480

using namespace sf;

Cloud::Cloud() {
    cloud[0].loadFromFile("resources/cloud1.png");
    cloud[1].loadFromFile("resources/cloud2.png");
    cloud[2].loadFromFile("resources/cloud3.png");
    cloud[3].loadFromFile("resources/cloud1.png");
    cloud[4].loadFromFile("resources/cloud2.png");

    srand(time(nullptr));

    for (int i = 0; i < cloudCnt; i++) {
        int randomOffset = rand() % 800;
        cloudPos[i].x = randomOffset;
        cloudPos[i].y = 60 + (i * 15);
        cloudSprite[i].setTexture(cloud[i]);
    }
}

int Cloud::getCloudCnt() { return cloudCnt; }

void Cloud::drawCloud(RenderWindow& w) {
    for (int i = 0; i < cloudCnt; i++) {
        w.draw(cloudSprite[i]);
    }
}

void Cloud::moveCloud() {
    for (int i = 0; i < cloudCnt; i++) {
        if (cloudPos[i].x <= -110)
        {
            cloudPos[i].x = WIDTH + 10;
        }
        else
        {
            cloudPos[i].x -= 3;
        }
        cloudSprite[i].setPosition(cloudPos[i].x, cloudPos[i].y);
    }
}