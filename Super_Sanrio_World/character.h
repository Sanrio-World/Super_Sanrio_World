#pragma once
#include <SFML/Graphics.hpp>

class character {
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

public:
	character(const std::string characterPath1,const std::string characterPath2);
	void jump(int kittyPos_x, int kittyPos_y, bool isBottom, bool isJumping, int gravity, int index);
	void moving(float frame, float frameSpeed, int index, int changeCharacter);
	void drawCharacter(sf::RenderWindow& window) const;


};