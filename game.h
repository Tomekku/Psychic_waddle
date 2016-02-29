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
    void onClick();


private:
    RenderWindow *window_PRIVATE;
    Ball player;
    Ball::Direction direction_PRIVATE;
    void play_PRIVATE();
    int mouseX_PRIVATE,mouseY_PRIVATE;
    Block blocks;
    float delta;
    sf::Clock clock;
};

#endif // GAME_H
