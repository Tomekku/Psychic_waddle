#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "player.h"
#include "block.h"
#include "mazegenerator.h"
#include <cmath>


using namespace sf;

class Game
{
public:
    Game(RenderWindow &win);
    void runGame();

private:
    bool _isCollisionNotExist();
    bool _isAbleToDraw();
    void _update();
    void _loadMenu();
    void _loadLevel();
    void _loading();
    void _createValidMaze();
    void _createMazeBorders();
    void _prepareWindow();

    enum Gamestate {MENU, END, LEVEL, LOADING};

    Gamestate _gameState;
    Font _font;
    RenderWindow *_window_ptr;
    Player _player;
    Player::Direction _playerDirection;
    MazeGenerator _mazeGenerator;
    Block _blocks;
    float _timeDelta;
    sf::Clock _clock;

};

#endif // GAME_H
