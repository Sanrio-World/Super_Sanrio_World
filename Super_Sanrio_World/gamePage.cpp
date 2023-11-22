#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "cloud.h"
#include "endPage.h"
#include "gamePage.h"
#include "obstacle.h"
#include "obstacle.h"
#include "startPage.h"
#include "character.h"
#include "position.h"
#include "scoreText.h"

using namespace sf;
using namespace std;

#define WIDTH 840
#define HEIGHT 480
#define KITTY_Y_BOTTOM 340

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

     // �ְ� ���
    int maxScore = 0;

    const int changeCharacter = 5;
    const int index = 0;
    float frame = 0.0f;
    float frameSpeed = 0.6f;

    float gravity = 15;
    bool isJumping = false;
    bool isBottom = true;

    CurrentP currentP = StartP;

    srand(time(nullptr)); // ���� �õ� �ʱ�ȭ

    Texture map;
    map.loadFromFile("resources/sanrio_map.png");
    Sprite mapSprite(map);
    mapSprite.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));

    Position kittyPos;
    kittyPos.x = 70;
    kittyPos.y = KITTY_Y_BOTTOM;

    // ��ֹ�
    Obstacle obs;

    // ����
    Cloud cloud;

    // ���� ������ ���� Clock
    Clock clock;
    float seconds = 0.0f;
    int score = 0;

    Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\H2GSRB.ttf"))
    {
        printf("��Ʈ �ҷ����� ����\n");
    }

  
    ScoreText maxscoreText(font, 53, 740, 5,Color::Magenta);
    ScoreText scoreText(font,33,10,5,Color::White);
    ScoreText scoreResultText(font, 100, 340, 165, Color::Magenta);

    // ���� ����� ��ư
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

            // Ű�� ������ ��
            if (e.type == Event::KeyPressed) {

                // ����ȭ�鿡�� Enter Key�� ������ ��
                if (e.key.code == Keyboard::Enter && currentP == StartP) {
                    currentP = GameP; // Enter Ű�� ������ ���� ȭ������ ��ȯ
                    cout << "Switched to GameP." << endl;
                }

                // ����ȭ�鿡�� Up Key�� ������ ��
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
                        cout << "Ŭ��" << endl;
                        score = 0;
                        gravity = 14;
                    }
                }
            }
        }

        if (currentP == StartP) {
            // ����ȭ�鿡�� ����ȭ������ �Ѿ��
            startP.draw(window);
        }
        if (currentP == GameP) {
            //����
            seconds += clock.restart().asSeconds();
            if (seconds >= 0.3f) {
                score++;
                seconds = 0.0f;

                // �ð� �帧�� ���� �ӵ� ��������
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

            // ���� ������ �ְ� ��� setting
            scoreText.setString(score);
            maxscoreText.setString(maxScore);

            // gampPage draws
            window.clear();
            window.draw(mapSprite);
           
            character.draw(window);
            scoreText.draw(window);
            maxscoreText.draw(window);
            cloud.drawCloud(window);
            for (int i = 0; i < obs.getObstacleCnt(); i++) {
                window.draw(obs.getSprites(i));
            }

            // ĳ���� ���� ����
            if (isJumping == true)
            {
                kittyPos.y -= gravity;
                character.setPosition(kittyPos.x, kittyPos.y);
            }
            else {
                kittyPos.y += gravity - 2;
                character.setPosition(kittyPos.x, kittyPos.y);
            }

            //�����ϰ� ���� ���� �� Y���� �ֵ���
            if (kittyPos.y >= KITTY_Y_BOTTOM) {
                kittyPos.y = KITTY_Y_BOTTOM;
                isBottom = true;
            }

            //���� ���� ����
            if (kittyPos.y <= KITTY_Y_BOTTOM - 210)
            {
                isJumping = false;
                score += 3;
            }
            character.setPosition(kittyPos.x, kittyPos.y);

            //��ֹ��� ĳ���� �浹
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

            //��ֹ� ������
            obs.moveObatacle();

            // ���� ������
            cloud.moveCloud();
        }
        if (currentP == EndP) {
            scoreResultText.setString(score);

            if (score > maxScore) maxScore = score;

            obs.setObstacleSpeed(7);

            window.clear();
            endP.draw(window);
            scoreResultText.draw(window);
            window.draw(reStartBtn_Sprite);

        }
        //ĳ���� �ٸ�������
        character.move(frame, frameSpeed, kittyPos.y, changeCharacter);
        HWND hWndConsole = GetConsoleWindow();
        ShowWindow(hWndConsole, SW_HIDE);
        window.display();
    };
}


