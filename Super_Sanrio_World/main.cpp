#include<SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>

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
    map.loadFromFile("resources/marioMap.bmp");
    Sprite mapSprite(map);

    Texture kitty;
    kitty.loadFromFile("resources/kitty.gif");
    Sprite kittySprite(kitty);
    
    Position kittyPos;
    kittyPos.x = 60;
    kittyPos.y = 350;

    Texture apple;
    apple.loadFromFile("resource/apple.png");
    Sprite appleSprite(apple);
    
   
    mapSprite.setTextureRect(IntRect(0, 0, 840, 480));
   
    const int gravity = 10;
    bool isJumping = false;
    bool isFloor = true;
   
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
    

   

    HWND hWndConsole = GetConsoleWindow();
    ShowWindow(hWndConsole, SW_HIDE);

  

        
        window.clear();
        window.draw(mapSprite);
        window.draw(kittySprite);
        window.display();
    }

    return 0;
}