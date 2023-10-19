#include<SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

using namespace std;
using namespace sf;

int main(void)
{
    Texture map;
    map.loadFromFile("resources/marioMap.bmp");
    Texture character;
    character.loadFromFile("resources/character.png");
    Sprite mapSprite;
    Sprite characterSprite;
    
    characterSprite.setTexture(character);
    characterSprite.setPosition(60,353);

    mapSprite.setTexture(map);
    mapSprite.setTextureRect(IntRect(0, 0, 840, 480));
    

    RenderWindow window(VideoMode(840, 480), "Super Sanrio World");

    window.setFramerateLimit(60);

    HWND hWndConsole = GetConsoleWindow();
    ShowWindow(hWndConsole, SW_HIDE);

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            
            if (e.type == Event::Closed) 
                window.close();
        }
        
        window.clear();
        window.draw(mapSprite);
        window.draw(characterSprite);
        window.display();
    }

    return 0;
}