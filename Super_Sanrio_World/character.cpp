#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "position.h"
#include "character.h"

#define WIDTH 840
#define HEIGHT 480

Character::Character(const std::string& characterPath1, const std::string& characterPath2) {
    kitty1.loadFromFile(characterPath1);
    kitty2.loadFromFile(characterPath2);
    kittySprite[0] = Sprite(kitty1);
    kittySprite[1] = Sprite(kitty2);
}
void Character::move(float& frame, float frameSpeed, int Kitty_y, int changeCharacter) {
    frame += frameSpeed;
    if (frame > changeCharacter && Kitty_y == 340) {
        frame -= changeCharacter;
        index++;
        if (index >= 2) index = 0;
    }
}
void Character::setPosition(int Kitty_x, int Kitty_y) {
    kittySprite[index].setPosition(Kitty_x, Kitty_y);
}
void Character::draw(RenderWindow& window){
    window.draw(kittySprite[index]);
}
Sprite Character::getKittySprite(int i) { return kittySprite[i]; }