#include "character.h"

Character::Character() {
    index = 0;
    changeCharacter = 5;
    frame = 0.0f;
    frameSpeed = 0.2f;
    gravity = 10;
    isJumping = false;
    isBottom = true;
    kittyPos_x = 70;
    kittyPos_y = 350;

    kitty1.loadFromFile("resources/character1.png");
    kitty2.loadFromFile("resources/character2.png");
    characterSprite[0].setTexture(kitty1);
    characterSprite[1].setTexture(kitty2);
}

void Character::update() {
    frame += frameSpeed;
    if (frame > 5) {
        frame -= 5;
        index++;
        if (index >= 2) index = 0;
    }

    if (isJumping) {
        kittyPos_y -= gravity;
        characterSprite[index].setPosition(kittyPos_x, kittyPos_y);
    }
    else {
        kittyPos_y += gravity;
        characterSprite[index].setPosition(kittyPos_x, kittyPos_y);
    }

    if (kittyPos_y >= 350) {
        kittyPos_y = 350;
        isBottom = true;
    }
    if (kittyPos_y <= 350 - 450) {
        isJumping = false;
    }
}
void Character::jump() {
    if (isBottom == true && isJumping == false) {
        isJumping = true;
        isBottom = false;
    }
    if (isJumping == true)
    {
        kittyPos_y -= gravity;
        characterSprite[index].setPosition(kittyPos_x, kittyPos_y);
    }
    else {
        kittyPos_y += gravity;
        characterSprite[index].setPosition(kittyPos_x, kittyPos_y);

    }

    //점프하고 있지 않을 시 Y값에 있도록
    if (kittyPos_y >= 350) {
        kittyPos_y = 350;
        isBottom = true;
    }
    //점프 높이 제한
    if (kittyPos_y <= 350 - 450)
    {
        isJumping = false;
    }
    characterSprite[index].setPosition(kittyPos_x, kittyPos_y);
}
void Character::moving() {
    //캐릭터 다리움직임
    frame += frameSpeed;
    if (frame > changeCharacter) {
        frame -= changeCharacter;
        index++;
        if (index >= 2) index = 0;
    }
}
void Character::draw(sf::RenderWindow window) {
    window.draw(characterSprite[index]);
}
