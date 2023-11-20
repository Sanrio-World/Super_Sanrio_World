#pragma once
#include <SFML/Graphics.hpp>
#include "character.h"

using namespace std;
using namespace sf;
class Game {
public:
	Game();
	void run();
private:
	RenderWindow window;
	Character character;
};