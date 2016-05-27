#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>


class Ball: public sf::Drawable, sf::Transformable
{
public:
    Ball();
    enum Direction {L,R,T,B};    //LEFT, RIGHT, TOP, BOTTOM
    void update(Direction direction, float delta, bool collision);
    float getRadius(){return radius_PRIVATE;}
    sf::Vector2f getPos(){return ball_PRIVATE.getPosition();}
    Direction getDir(){return direction;}

private:
    Direction direction;
    sf::Vector2f lerp(sf::Vector2f from, sf::Vector2f to, float t);
    sf::CircleShape ball_PRIVATE;
    float x_PRIVATE, y_PRIVATE, speed_PRIVATE, radius_PRIVATE;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::Vector2f setVectorByDirection(Direction direction);
};

#endif // BALL_H
