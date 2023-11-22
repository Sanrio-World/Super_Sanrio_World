#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "cloud.h"
#include "endPage.h"
#include "gamePage.h"
#include "startPage.h"
//#include "character.h"
#include "position.h"
//#include "obstacle.h"
#include "scoreText.h"

using namespace sf;
using namespace std;

#define WIDTH 840
#define HEIGHT 480
#define KITTY_Y_BOTTOM 315

enum CurrentP {
    StartP,
    GameP,
    EndP
};

void gamePage::run() {
    srand(time(nullptr)); // ���� �õ� �ʱ�ȭ

    RenderWindow window(VideoMode(840, 480), "Super Sanrio World");
    window.setFramerateLimit(60);

    //������ �ҷ�����
    startPage startP("resources/startpage.png");
    endPage endP("resources/endpage.png");

     // �ְ� ���
    int maxScore = 0;

    const int changeCharacter = 5;
    int index = 0;
    float frame = 0.0f;
    float frameSpeed = 0.6f;


    float gravity = 13;
    bool isJumping = false;
    bool isBottom = true;

    CurrentP currentP = StartP;

    //���
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

    //ĳ���� ��ġ - ȿ��
    Position kittyPos;
    kittyPos.x = 70;
    kittyPos.y = KITTY_Y_BOTTOM;

    // ĳ���� �ʱ� ��ġ ����
    kittySprite[index].setPosition(kittyPos.x, kittyPos.y);

    // ��ֹ�
    const int obstacleCnt = 3;
    Texture obstacle[obstacleCnt];
    Position obstaclePos[obstacleCnt];
    Sprite obstacleSprite[obstacleCnt];
    obstacle[0].loadFromFile("resources/obstacle1.png");
    obstacle[1].loadFromFile("resources/obstacle2.png");
    obstacle[2].loadFromFile("resources/obstacle4.png");

    float obstacleSpeed = 7;

    int obstaclePosition = rand() % 920 + 780;

    for (int i = 0; i < obstacleCnt; i++) {
        obstaclePos[i].x = obstaclePosition + (i * 310);
        obstaclePos[i].y = 350;
        obstacleSprite[i].setTexture(obstacle[i]);
    }

    // ���� - ����
    Cloud cloud;

    // ���� ������ ���� �ð�
    Clock clock;
    float seconds = 0.0f;
    int score = 0;

    Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\H2GSRB.ttf"))
    {
        printf("��Ʈ �ҷ����� ����\n");
    }

    //�ؽ�Ʈ(����) �ҷ�����
    ScoreText maxscoreText(font, 53, 740, 5,Color::Magenta);
    ScoreText scoreText(font,33,10,5,Color::White);
    ScoreText scoreResultText(font, 100, 340, 165, Color::Magenta);

    // ���� ����� ��ư - ����
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

                // ����ȭ�鿡�� Enter Key�� ������ �� - ����
                if (e.key.code == Keyboard::Enter && currentP == StartP) {
                    currentP = GameP; // Enter Ű�� ������ ���� ȭ������ ��ȯ
                    cout << "Switched to GameP." << endl;
                }

                // ����ȭ�鿡�� Up Key�� ������ �� - ȿ��
                if (e.key.code == Keyboard::Up && currentP == GameP) {
                    if (isBottom == true && isJumping == false) {
                        isJumping = true;
                        isBottom = false;
                    }
                }
            }

            // ����� ��ư Ŭ�� ���� - ����
            if (e.type == Event::MouseButtonPressed) { // ���콺�� ������
                if (e.mouseButton.button == Mouse::Left) { // ���콺�� ���� ��ư�� ������
                    Vector2i mousePos = Mouse::getPosition(window); // ������ �ȿ��� ���콺�� ���� ��

                    // ����� ��ư�� ��迡 ���콺�� ���� ���� ���ԵǾ��ٸ�
                    if (reStartBtn_Sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        currentP = StartP; // Start �������� ����
                        score = 0;      // ���� �ʱ�ȭ
                        gravity = 13;   // ������ �� �������� �ӵ� �ʱ�ȭ
                    }
                }
            }
        }

        // ȭ�� ��ȯ ���� - ����
        if (currentP == StartP) {
            // ����ȭ�鿡�� ����ȭ������ �Ѿ��
            startP.draw(window);
        }
        if (currentP == GameP) {
            //���� - ȿ��
            seconds += clock.restart().asSeconds();
            //0.3�ʿ� 1���� ��������
            if (seconds >= 0.3f) {
                score++;
                seconds = 0.0f;

                // �ð� �帧�� ���� �ӵ�, ������ �� �������� �ӵ� ���� - ����
                if (seconds >= 90) {
                    for (int i = 0; i < obstacleCnt; i++) {
                        obstacleSpeed += 0.1;
                        gravity++;
                    }
                }
                if (seconds >= 200) {
                    for (int i = 0; i < obstacleCnt; i++) {
                        obstacleSpeed += 0.2;
                        gravity++;
                    }
                }
            }

            // ���� ����
            scoreText.setString(score);

            // �ְ� ��� ��� - ����
            maxscoreText.setString(maxScore);

            // gampPage draws
            window.clear();
            window.draw(mapSprite);
            window.draw(kittySprite[index]);
            scoreText.draw(window);
            maxscoreText.draw(window);
            cloud.drawCloud(window);
            for (int i = 0; i < obstacleCnt; i++) {
                window.draw(obstacleSprite[i]);
            }

            // ĳ���� ���� ����
            if (isJumping == true)
            {
                kittyPos.y -= gravity;
                kittySprite[index].setPosition(kittyPos.x, kittyPos.y);
            }
            else {
                kittyPos.y += gravity - 2;
                kittySprite[index].setPosition(kittyPos.x, kittyPos.y);
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
            }
            kittySprite[index].setPosition(kittyPos.x, kittyPos.y);

            //��ֹ��� ĳ���� �浹 -ȿ��
            FloatRect characterBounds = kittySprite[index].getGlobalBounds();
            for (int i = 0; i < obstacleCnt; i++) {
                FloatRect obstacleBounds = obstacleSprite[i].getGlobalBounds();

                if (characterBounds.intersects(obstacleBounds)) {
                    currentP = EndP;
                    for (int j = 0; j < obstacleCnt; j++)
                        obstaclePos[j].x = WIDTH;
                    break;
                }
            }

            int distance = rand() % 330 + 310;

            //��ֹ� ������ 
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


            // ���� ������
            cloud.moveCloud();
        }
        if (currentP == EndP) {
            scoreResultText.setString(score);

            if (score > maxScore) maxScore = score;

            obstacleSpeed = 7;

            window.clear();
            endP.draw(window);
            scoreResultText.draw(window);
            window.draw(reStartBtn_Sprite);

        } // ȭ�� ��ȯ ��� - ����

        //ĳ���� �ٸ������� - ȿ��
        frame += frameSpeed;
        // ŰƼ�� �������� ���� ���� �޸��� ���
        // �������Ÿ� �ذ�
        if (frame > changeCharacter && kittyPos.y == KITTY_Y_BOTTOM) {
            frame -= changeCharacter;
            index++;
            if (index >= 2) index = 0;
        }
        HWND hWndConsole = GetConsoleWindow();
        ShowWindow(hWndConsole, SW_HIDE);
        window.display();
    };
}