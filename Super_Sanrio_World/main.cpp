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
	map.loadFromFile("resources/map.png");
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

		if (applePos.x <= -1)
		{
			applePos.x = WIDTH;
		}
		else
		{
			applePos.x -= 5;
		}
		appleSprite.setPosition(applePos.x, applePos.y);




		HWND hWndConsole = GetConsoleWindow();
		ShowWindow(hWndConsole, SW_HIDE);




		window.clear();
		window.draw(mapSprite);
		window.draw(kittySprite);
		window.draw(appleSprite);
		window.display();
	}

	return 0;
}