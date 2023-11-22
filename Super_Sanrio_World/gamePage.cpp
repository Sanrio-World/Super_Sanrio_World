#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "gamePage.h"
#include "startPage.h"
#include "endPage.h"
#include "obstacle.h"
#include "character.h"
#include "position.h"
#include "cloud.h"

using namespace sf;
using namespace std;

#define WIDTH 840
#define HEIGHT 480
#define KITTY_Y_BOTTOM 320

enum CurrentP {
    StartP,
    GameP,
    EndP
};

void gamePage::run() {
    RenderWindow window(VideoMode(840, 480), "Super Sanrio World");
    window.setFramerateLimit(60);

    startPage startP("resources/startpage.png");
    endPage endP("resources/endpage.png");
    Character character("resources/character1.png", "resources/character2.png");

     // 최고 기록
    int maxScore = 0;

    const int changeCharacter = 5;
    const int index = 0;
    float frame = 0.0f;
    float frameSpeed = 0.6f;

    float gravity = 15;
    bool isJumping = false;
    bool isBottom = true;

    CurrentP currentP = StartP;

    srand(time(nullptr)); // 랜덤 시드 초기화

    Texture map;
    map.loadFromFile("resources/sanrio_map.png");
    Sprite mapSprite(map);
    mapSprite.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));

    Position kittyPos;
    kittyPos.x = 70;
    kittyPos.y = KITTY_Y_BOTTOM;

    // 장애물
    Obstacle obs;

    // 구름
    Cloud cloud;

    // 점수 측정을 위한 Clock
    Clock clock;
    float seconds = 0.0f;
    int score = 0;

    Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\H2GSRB.ttf"))
    {
        printf("폰트 불러오기 실패\n");
    }

    Text maxScoreText;
    maxScoreText.setFont(font);
    maxScoreText.setCharacterSize(53);
    maxScoreText.setFillColor(Color::Magenta);
    maxScoreText.setPosition(740, 5);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(33);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 5);

    Text scoreResultText;
    scoreResultText.setFont(font);
    scoreResultText.setCharacterSize(100);
    scoreResultText.setFillColor(Color::Magenta);
    scoreResultText.setPosition(340, 165);

    // 게임 재시작 버튼
    Texture restartBtn;
    restartBtn.loadFromFile("resources/restart_btn.png");
    Sprite reStartBtn_Sprite(restartBtn);
    reStartBtn_Sprite.setPosition(550, 350);

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

            if (e.type == Event::MouseButtonPressed) {
                if (e.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(window);
                    Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                    if (reStartBtn_Sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                        currentP = StartP;
                        cout << "클릭" << endl;
                        score = 0;
                        gravity = 14;
                    }
                }
            }
        }

        if (currentP == StartP) {
            // 시작화면에서 게임화면으로 넘어가게
            startP.draw(window);
        }
        if (currentP == GameP) {
            //점수
            seconds += clock.restart().asSeconds();
            if (seconds >= 0.3f) {
                score++;
                seconds = 0.0f;

                // 시간 흐름에 따라 속도 빨라지기
                if (seconds >= 90) {
                    for (int i = 0; i < obs.getObstacleCnt(); i++) {
                        obs.sumSpeed(0.1);
                        gravity++;
                    }
                }
                if (seconds >= 200) {
                    for (int i = 0; i < obs.getObstacleCnt(); i++) {
                        obs.sumSpeed(0.2);
                        gravity++;
                    }
                }
            }

            // 현재 점수와 최고 기록 setting
            scoreText.setString(to_string(score));
            maxScoreText.setString(to_string(maxScore));

            // gampPage draws
            window.clear();
            window.draw(mapSprite);
           
            character.draw(window);
            window.draw(scoreText);
            window.draw(maxScoreText);
            cloud.drawCloud(window);
            for (int i = 0; i < obs.getObstacleCnt(); i++) {
                window.draw(obs.getSprites(i));
            }

            // 캐릭터 점프 설정
            if (isJumping == true)
            {
                kittyPos.y -= gravity;
                character.setPosition(kittyPos.x, kittyPos.y);
            }
            else {
                kittyPos.y += gravity - 2;
                character.setPosition(kittyPos.x, kittyPos.y);
            }

            //점프하고 있지 않을 시 Y값에 있도록
            if (kittyPos.y >= KITTY_Y_BOTTOM) {
                kittyPos.y = KITTY_Y_BOTTOM;
                isBottom = true;
            }

            //점프 높이 제한
            if (kittyPos.y <= KITTY_Y_BOTTOM - 210)
            {
                isJumping = false;
                score += 3;
            }
            character.setPosition(kittyPos.x, kittyPos.y);

            //장애물과 캐릭터 충돌
           FloatRect characterBounds = character.getKittySprite(index).getGlobalBounds();
           for (int i = 0; i < obs.getObstacleCnt(); i++) {
               FloatRect obstacleBounds = obs.getSprites(i).getGlobalBounds();

               if (characterBounds.intersects(obstacleBounds)) {
                   currentP = EndP;
                   for (int j = 0; j < obs.getObstacleCnt(); j++)
                       obs.setObstaclePosX(j, WIDTH);
                   break;
               }
           }

            int distance = rand() % 330 + 310;

            //장애물 움직임
            obs.moveObatacle();

            // 구름 움직임
            cloud.moveCloud();
        }
        if (currentP == EndP) {
            scoreResultText.setString(to_string(score));

            if (score > maxScore) maxScore = score;

            obs.setObstacleSpeed(7);

            window.clear();
            endP.draw(window);
            window.draw(scoreResultText);
            window.draw(reStartBtn_Sprite);

        }
        //캐릭터 다리움직임
        character.move(frame, frameSpeed, kittyPos.y, changeCharacter);
        HWND hWndConsole = GetConsoleWindow();
        ShowWindow(hWndConsole, SW_HIDE);
        window.display();
    };
}


