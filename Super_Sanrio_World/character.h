#pragma
#include <SFML/Graphics.hpp>

class Character {
public:
	Character();

	void update();
	void jump();
	void moving();
	void draw(sf::RenderWindow window);
private:
	sf::Sprite characterSprite[2];
	sf::Texture kitty1;
	sf::Texture kitty2;
	int index;
	int changeCharacter;
	float frame;
	float frameSpeed;
	int gravity;
	bool isJumping;
	bool isBottom;
	int kittyPos_x;
	int kittyPos_y;

};