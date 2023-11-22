#include "gamePage.h"
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace sf;



int main(void)
{
    Music music;
    if (!music.openFromFile("resources/sanrio_world_bgm.ogg"))
        return -1; // error
    music.play();

    gamePage gameP;
    gameP.run();
    return 0;
}