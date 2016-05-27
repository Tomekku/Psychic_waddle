#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "ball.h"
#include "block.h"
#include "mazegenerator.h"
#include <cmath>


using namespace sf;

class Game
{
public:
    Game(RenderWindow &win);
    void update();
    void runGame();
    bool isCollisionNotExist();
    bool isAbleToDraw();
    void menu();
    void level();
    void loading();
    void createValidMaze();

private:
    enum Gamestate {MENU, END, LEVEL, LOADING};
    Gamestate state;
    Font font;
    RenderWindow *window_PRIVATE;
    Ball player;
    Ball::Direction direction_PRIVATE;
    MazeGenerator Maze_PRIVATE;
    void play_PRIVATE();
    Block blocks;
    float delta;
    sf::Clock clock;

};

#endif // GAME_H
