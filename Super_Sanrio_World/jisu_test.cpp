#include<SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

#define WIDTH 840
#define HEIGHT 480
using namespace std;
using namespace sf;

struct Position {
    int x;
    int y;
};
int main(void)
{

    RenderWindow window(VideoMode(840, 480), "Super Sanrio World");
    window.setFramerateLimit(60);

    Texture map;
    map.loadFromFile("resources/sanrioMap.bmp");
    Sprite mapSprite(map);
    mapSprite.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));

    Texture kitty;
    kitty.loadFromFile("resources/kitty.gif");
    Sprite kittySprite(kitty);

    Position kittyPos;
    kittyPos.x = 60;
    kittyPos.y = 350;

    Texture apple;
    apple.loadFromFile("resources/apple.png");
    Sprite appleSprite(apple);
    Position applePos;
    applePos.x = 100;
    applePos.y = 370;

    const int cloudCnt = 2;

    Texture cloud[cloudCnt];
    Position cloudPos[cloudCnt];
    Sprite cloudSprite[cloudCnt];

    cloud[0].loadFromFile("resources/cloud1.png");
    cloud[1].loadFromFile("resources/cloud2.png");


    for (int i = 0; i < cloudCnt; i++) {
        cloudPos[i].x = 10;
        cloudPos[i].y = 60;
        cloudSprite[i].setTexture(cloud[i]);
    }

    const int gravity = 10;

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {

            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            kittyPos.y -= gravity;
        }
        else {
            kittyPos.y = 350;
        }
        kittySprite.setPosition(kittyPos.x, kittyPos.y);

        if (applePos.x <= 0)
        {
            applePos.x = WIDTH;
        }
        else
        {
            applePos.x -= 5;
        }
        appleSprite.setPosition(applePos.x, applePos.y);

        for (int i = 0; i < cloudCnt; i++) {
            if (cloudPos[i].x <= 0)
            {
                cloudPos[i].x = WIDTH;
            }
            else
            {
                cloudPos[i].x -= 2+i;
            }
            cloudSprite[i].setPosition(cloudPos[i].x, cloudPos[i].y);
        }



        HWND hWndConsole = GetConsoleWindow();
        ShowWindow(hWndConsole, SW_HIDE);




        window.clear();
        window.draw(mapSprite);
        window.draw(kittySprite);
        window.draw(appleSprite);
        for (int i = 0; i < cloudCnt; i++) {
            window.draw(cloudSprite[i]);
        }
        window.display();
    }

    return 0;
}