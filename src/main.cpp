#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800,600),"Kulka");
    Game game(window);
    game.runGame();
    return 0;
}

