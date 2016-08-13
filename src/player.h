#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

using namespace sf;

class Player: public Drawable, Transformable
{
public:
    Player();
    enum Direction {LEFT,RIGHT,TOP,BOTTOM, STOP};
    bool playerUpdate(Direction _playerDirection, float timeDelta, bool collision);
    float getPlayerRadius(){return _playerRadius;}
    Vector2f getPlayerPosition(){return _player.getPosition();}
    Direction getPlayerDirection(){return _playerDirection;}
    float getPlayerThickness(){return _player.getOutlineThickness();}

private:
    Direction _playerDirection;
    Vector2f createOffset(Vector2f from, Vector2f to, float distance);
    sf::CircleShape _player;
    Vector2f _playerPosition;
    float _playerSpeed, _playerRadius;
    virtual void draw(RenderTarget &target, RenderStates states) const;
    Vector2f setVectorByDirection(Direction _playerDirection);
};

#endif // BALL_H
