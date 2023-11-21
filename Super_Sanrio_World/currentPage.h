#pragma once

#include <SFML/Graphics.hpp>
#define WIDTH 840
#define HEIGHT 480
using namespace sf;
enum class CurrentP {
    Start,
    Game,
    End
};

class CurrentPage {
public:
    CurrentPage();

private:
    CurrentP currentPage;
    
};
