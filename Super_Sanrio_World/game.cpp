#include<SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

#include "game.h"

Game::Game() {
}

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
	GameP
};

void Game::run()
{
	RenderWindow window(VideoMode(840, 480), "Super Sanrio World");
	window.setFramerateLimit(60);

	CurrentP currentP = StartP;

	Texture map;
	map.loadFromFile("resources/sanrio_map.png");
	Sprite mapSprite(map);
	mapSprite.setTextureRect(IntRect(0, 0, WIDTH, HEIGHT));


	const int obstacleCnt = 2;
	Texture obstacle[obstacleCnt];
	Position obstaclePos[obstacleCnt];
	Sprite obstacleSprite[obstacleCnt];
	obstacle[0].loadFromFile("resources/obstacle1.png");
	obstacle[1].loadFromFile("resources/obstacle2.png");

	for (int i = 0; i < obstacleCnt; i++) {
		obstaclePos[i].x = 240 + (i * 10);
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

	Clock clock;
	float seconds = 0.0f;
	int score = 0;

	Font font;
	if (!font.loadFromFile("C:\\Windows\\Fonts\\H2GSRB.ttf"))
	{
		printf("폰트 불러오기 실패\n");
	}

	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(0, 0);

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
			window.draw(scoreText);
			for (int i = 0; i < cloudCnt; i++) {
				window.draw(cloudSprite[i]);
			}
			for (int i = 0; i < obstacleCnt; i++) {
				window.draw(obstacleSprite[i]);
			}

			

			//장애물과 캐릭터 충돌
			bool collision = false;
			FloatRect characterBounds = kittySprite[index].getGlobalBounds();
			for (int i = 0; i < obstacleCnt; i++) {
				FloatRect obstacleBounds = obstacleSprite[i].getGlobalBounds();

				if (characterBounds.intersects(obstacleBounds)) {
					collision = true;
					break;
				}
			}
			if (collision == true) {
				window.close();
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
		
	

		HWND hWndConsole = GetConsoleWindow();
		ShowWindow(hWndConsole, SW_HIDE);
		window.display();
	}
}