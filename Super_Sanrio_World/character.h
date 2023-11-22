#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "string"

#include "position.h"

using namespace sf;
using namespace std;
class character : Position {
public :
	character(const std::string&, const std::string&);
	void move(float&, float, int, int);
	void setPosition(int, int);
	void draw(RenderWindow&);
    Sprite getKittySprite(int);
private:
   
    static const int count = 2;
    int index=0;
    Texture kitty1;
    Texture kitty2;
    Sprite kittySprite[count];
    int Kitty_x;
    int Kitty_y;
    int changeCharacter;
    float frame;
    float frameSpeed;
   
};