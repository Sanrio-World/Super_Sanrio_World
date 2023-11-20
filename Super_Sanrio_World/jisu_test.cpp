#include<SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

// #include "start_page.h"

#define WIDTH 840
#define HEIGHT 480

using namespace std;
using namespace sf;

struct Position {
    int x;
    int y;
};

enum CurrentP {
    StartP,
    GameP,
    EndP
};

int main(void)
{
    RenderWindow window(VideoMode(840, 480), "Super Sanrio World");
    window.setFramerateLimit(60);

    const int changeCharacter = 5;
    int index = 0;
    float frame = 0.0f;
    float frameSpeed = 0.2f;

    const int gravity = 10;
    bool isJumping = false;
    bool isBottom = true;

    CurrentP currentP = StartP;

    Texture map;
    map.loadFromFile("resources/sanrio_map.png");
    Sprite mapSprite(map);
    mapSprite.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));

    Texture kitty1;
    kitty1.loadFromFile("resources/character1.png");
    Texture kitty2;
    kitty2.loadFromFile("resources/character2.png");
    Sprite kittySprite[2];
    kittySprite[0] = Sprite(kitty1);
    kittySprite[1] = Sprite(kitty2);

    const int KITTY_Y_BOTTOM = HEIGHT - 150;

    Position kittyPos;
    kittyPos.x = 70;
    kittyPos.y = KITTY_Y_BOTTOM;

    const int obstacleCnt = 2;
    Texture obstacle[obstacleCnt];
    Position obstaclePos[obstacleCnt];
    Sprite obstacleSprite[obstacleCnt];
    obstacle[0].loadFromFile("resources/obstacle1.png");
    obstacle[1].loadFromFile("resources/obstacle2.png");

    for (int i = 0; i < obstacleCnt; i++) {
        obstaclePos[i].x = 900;
        obstaclePos[i].y = 350;
        obstacleSprite[i].setTexture(obstacle[i]);
    }

    const int cloudCnt = 5;
    Texture cloud[cloudCnt];
    Position cloudPos[cloudCnt];
    Sprite cloudSprite[cloudCnt];

    cloud[0].loadFromFile("resources/cloud1.png");
    cloud[1].loadFromFile("resources/cloud2.png");
    cloud[2].loadFromFile("resources/cloud3.png");
    cloud[3].loadFromFile("resources/cloud1.png");
    cloud[4].loadFromFile("resources/cloud2.png");


    for (int i = 0; i < cloudCnt; i++) {
        cloudPos[i].x = 10;
        cloudPos[i].y = 60 + (i * 15);
        cloudSprite[i].setTexture(cloud[i]);
    }


    Texture startPage;
    startPage.loadFromFile("resources/startpage.png");
    Sprite startPage_Sprite(startPage);
    startPage_Sprite.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));

    Texture endPage;
    endPage.loadFromFile("resources/endpage.png");
    Sprite endPage_Sprite(endPage);
    endPage_Sprite.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));

    Clock clock;
    float seconds = 0.0f;
    int score = 0;

    Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\H2GSRB.ttf"))
    {
        printf("폰트 불러오기 실패\n");
        return -1;
    }

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(0, 0);

    Text scoreResultText;
    scoreResultText.setFont(font);
    scoreResultText.setCharacterSize(100);
    scoreResultText.setFillColor(Color::Black);
    scoreResultText.setPosition(340, 165);

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {

            if (e.type == Event::Closed) {
                window.close();
                cout << "Window is closed." << endl;
            }

            // 키가 눌렸을 때
            if (e.type == Event::KeyPressed) {

                // 시작화면에서 Enter Key가 눌렸을 때
                if (e.key.code == Keyboard::Enter && currentP == StartP) {
                    currentP = GameP; // Enter 키를 누르면 게임 화면으로 전환
                    cout << "Switched to GameP." << endl;
                }

                // 게임화면에서 Up Key가 눌렸을 때
                if (e.key.code == Keyboard::Up && currentP == GameP) {
                    if (isBottom == true && isJumping == false) {
                        isJumping = true;
                        isBottom = false;
                    }
                }
            }
        }

        if (currentP == StartP) {
            window.clear();
            // 시작화면에서 게임화면으로 넘어가게
            window.draw(startPage_Sprite);
        }
        if (currentP == GameP) {
            //점수
            seconds += clock.restart().asSeconds();
            if (seconds >= 0.3f) {
                score++;
                seconds = 0.0f;
            }
            scoreText.setString("Score: " + to_string(score));

            window.clear();
            window.draw(mapSprite);
            window.draw(kittySprite[index]);
            window.draw(scoreText);
            for (int i = 0; i < cloudCnt; i++) {
                window.draw(cloudSprite[i]);
            }
            for (int i = 0; i < obstacleCnt; i++) {
                window.draw(obstacleSprite[i]);
            }

            if (isJumping == true)
            {
                kittyPos.y -= gravity;
                kittySprite[index].setPosition(kittyPos.x, kittyPos.y);
            }
            else {
                kittyPos.y += gravity;
                kittySprite[index].setPosition(kittyPos.x, kittyPos.y);

            }

            //점프하고 있지 않을 시 Y값에 있도록
            if (kittyPos.y >= KITTY_Y_BOTTOM) {
                kittyPos.y = KITTY_Y_BOTTOM;
                isBottom = true;
            }
            //점프 높이 제한
            if (kittyPos.y <= KITTY_Y_BOTTOM - 450)
            {
                isJumping = false;
            }
            kittySprite[index].setPosition(kittyPos.x, kittyPos.y);

            //장애물과 캐릭터 충돌
            currentP = GameP;
            FloatRect characterBounds = kittySprite[index].getGlobalBounds();
            for (int i = 0; i < obstacleCnt; i++) {
                FloatRect obstacleBounds = obstacleSprite[i].getGlobalBounds();

                if (characterBounds.intersects(obstacleBounds)) {
                    currentP = EndP;
                    break;
                }
            }

            
            //장애물 움직임
            for (int i = 0; i < obstacleCnt; i++) {
                if (obstaclePos[i].x <= 0)
                {
                    obstaclePos[i].x = WIDTH;
                }
                else
                {
                    obstaclePos[i].x -= 3 - i;
                }
                obstacleSprite[i].setPosition(obstaclePos[i].x, obstaclePos[i].y);
            }

            // 구름 움직임
            for (int i = 0; i < cloudCnt; i++) {
                if (cloudPos[i].x <= -110)
                {
                    cloudPos[i].x = WIDTH + 10;
                }
                else
                {
                    cloudPos[i].x -= 2 + i;
                }
                cloudSprite[i].setPosition(cloudPos[i].x, cloudPos[i].y);
            }
        }
        if (currentP == EndP) {
            scoreResultText.setString(to_string(score));
            //scoreResultText.setString(to_string(100));

            window.clear();
            window.draw(endPage_Sprite);
            window.draw(scoreResultText);

        }

        //캐릭터 다리움직임
        frame += frameSpeed;
        if (frame > changeCharacter) {
            frame -= changeCharacter;
            index++;
            if (index >= 2) index = 0;
        }

        HWND hWndConsole = GetConsoleWindow();
        ShowWindow(hWndConsole, SW_HIDE);
        window.display();
    }
    return 0;
}