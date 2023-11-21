#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

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

class Button {
public:
    Button(const std::string& texturePath, Vector2f position) {
        /*if (!texture.loadFromFile(texturePath)) {
            cout <<
        }*/

        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    bool isClicked(Vector2f mousePos) const {
        return sprite.getGlobalBounds().contains(mousePos);
    }

    void draw(RenderWindow& window) const {
        window.draw(sprite);
    }

private:
    Texture texture;
    Sprite sprite;
};

int main(void)
{
    RenderWindow window(VideoMode(840, 480), "Super Sanrio World");
    window.setFramerateLimit(60);

    // 배경 음악
    Music music;
    if (!music.openFromFile("resources/sanrio_world_bgm.ogg"))
        return -1; // error
    music.play();

    // 최고 기록
    int maxScore = 0;

    const int changeCharacter = 5;
    int index = 0;
    float frame = 0.0f;
    float frameSpeed = 0.6f;

    float gravity = 14;
    bool isJumping = false;
    bool isBottom = true;

    CurrentP currentP = StartP;

    srand(time(nullptr)); // 랜덤 시드 초기화

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

    float obstacleSpeed[2];
    obstacleSpeed[0] = rand() % 6 + 4;
    obstacleSpeed[1] = rand() % 6 + 4;

    for (int i = 0; i < obstacleCnt; i++) {
        int obstaclePosition = rand() % 880 + 700;
        obstaclePos[i].x = obstaclePosition;
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
        int randomOffset = rand() % 800;
        cloudPos[i].x = randomOffset;
        cloudPos[i].y = 60 + (i * 15);
        cloudSprite[i].setTexture(cloud[i]);
    }

   
    Texture startPage;
    startPage.loadFromFile("resources/startpage.png");
    Sprite startPage_Sprite(startPage);
    startPage_Sprite.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));

    //endPage.cpp
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

    //Button restartBtn("resources/restart_btn.png", Vector2f(550, 350));


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
                if (score >= 30) {
                    for (int i = 0; i < obstacleCnt; i++) {
                        obstacleSpeed[i] += 0.2;
                        gravity = 14;
                    }
                }
                if (score >= 90) {
                    for (int i = 0; i < obstacleCnt; i++) {
                        obstacleSpeed[i] += 0.2;
                        gravity = 14;
                    }
                }
                if (score >= 200) {
                    for (int i = 0; i < obstacleCnt; i++) {
                        obstacleSpeed[i] += 0.2;
                        gravity++;
                    }
                }
            }
            scoreText.setString(to_string(score));
            maxScoreText.setString(to_string(maxScore));

            window.clear();
            window.draw(mapSprite);
            window.draw(kittySprite[index]);
            window.draw(scoreText);
            window.draw(maxScoreText);
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
                kittyPos.y += gravity - 3;
                kittySprite[index].setPosition(kittyPos.x, kittyPos.y);

            }

            //점프하고 있지 않을 시 Y값에 있도록
            if (kittyPos.y >= KITTY_Y_BOTTOM) {
                kittyPos.y = KITTY_Y_BOTTOM;
                isBottom = true;
            }
            //점프 높이 제한
            if (kittyPos.y <= KITTY_Y_BOTTOM - 250)
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
                    obstaclePos[0].x = WIDTH;
                    obstaclePos[1].x = WIDTH;
                    break;
                }
            }

            //장애물 움직임
            for (int i = 0; i < obstacleCnt; i++) {
                if (obstaclePos[i].x <= -30)
                {
                    obstacleSpeed[i] = rand() % 7 + (obstacleSpeed[i] - 3);
                    obstaclePos[i].x = WIDTH;
                }
                else
                {
                    obstaclePos[i].x -= obstacleSpeed[i];
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
                    cloudPos[i].x -= 3;
                }
                cloudSprite[i].setPosition(cloudPos[i].x, cloudPos[i].y);
            }
        }
        if (currentP == EndP) {
            scoreResultText.setString(to_string(score));

            if (score > maxScore) maxScore = score;

            obstacleSpeed[0] = rand() % 5 + 3;
            obstacleSpeed[1] = rand() % 5 + 3;

            window.clear();
            window.draw(endPage_Sprite);
            window.draw(scoreResultText);
            window.draw(reStartBtn_Sprite);

        }

        //캐릭터 다리움직임
        frame += frameSpeed;
        if (frame > changeCharacter && kittyPos.y == KITTY_Y_BOTTOM) {
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