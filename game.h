#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "block.h"

using namespace sf;

class Game
{
public:
    Game(RenderWindow &win);
    void update();
    void runGame();
    bool isCollisionExist();
    bool isAbleToDraw();

private:
    RenderWindow *window_PRIVATE;
    Ball::Direction direction_PRIVATE;
    void play_PRIVATE();
};

#endif // GAME_H
