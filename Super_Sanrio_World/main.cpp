#include<SFML/Graphics.hpp>
#include <windows.h>

using namespace sf;

int main(void)
{
    RenderWindow window(VideoMode(640, 480), "Super Sanrio World");

    window.setFramerateLimit(60);

    HWND hWndConsole = GetConsoleWindow();
    ShowWindow(hWndConsole, SW_HIDE);

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            // 윈도우의 x를 눌렀을 때 창이 닫아지도록
            if (e.type == Event::Closed) // x표를 누른다면
                window.close();
        }

        window.clear();

        window.display();
    }

    return 0;
}