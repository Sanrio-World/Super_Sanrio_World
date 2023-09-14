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
            // �������� x�� ������ �� â�� �ݾ�������
            if (e.type == Event::Closed) // xǥ�� �����ٸ�
                window.close();
        }

        window.clear();

        window.display();
    }

    return 0;
}