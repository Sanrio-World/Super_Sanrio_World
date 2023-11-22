#include "character.h"

character::character(const std::string characterPath1, const std::string characterPath2) {
    kitty1.loadFromFile(characterPath1);
    kitty2.loadFromFile(characterPath2);
    characterSprite[0].setTexture(kitty1);
    characterSprite[1].setTexture(kitty2);
}

void character::jump(int kittyPos_x,int kittyPos_y,bool isBottom,bool isJumping,int gravity,int index) {
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

    //�����ϰ� ���� ���� �� Y���� �ֵ���
    if (kittyPos_y >= 350) {
        kittyPos_y = 350;
        isBottom = true;
    }
    //���� ���� ����
    if (kittyPos_y <= 350 - 450)
    {
        isJumping = false;
    }
    characterSprite[index].setPosition(kittyPos_x, kittyPos_y);
}
void character::moving(float frame,float frameSpeed,int index,int changeCharacter) {
    //ĳ���� �ٸ�������
    frame += frameSpeed;
    if (frame > changeCharacter) {
        frame -= changeCharacter;
        index++;
        if (index >= 2) index = 0;
    }
}
void character::drawCharacter(sf::RenderWindow& window) const {
    window.clear();
    window.draw(characterSprite[index]);
}

