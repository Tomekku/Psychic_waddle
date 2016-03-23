#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "ball.h"
#include "block.h"
#include "mazegenerator.h"


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
    void menu();
    void level();
    void loading();

protected:
    enum Gamestate {MENU, END, LEVEL, LOADING};
    Gamestate state;
    Font font;
private:
    RenderWindow *window_PRIVATE;
    Ball player;
    Ball::Direction direction_PRIVATE;
    MazeGenerator Maze_PRIVATE;
    void play_PRIVATE();
    int mouseX_PRIVATE,mouseY_PRIVATE;
    Block blocks;
    float delta;
    sf::Clock clock;

};

#endif // GAME_H
