#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>


class Ball: public sf::Drawable, sf::Transformable
{
public:

    Ball();
    enum Direction {L,R,T,B,LT,LB,RT,RB};    //LEFT, RIGHT, TOP, BOTTOM, LTOP, LBOTTOM, RTOP, RBOTTOM
    Direction direction;
    sf::Vector2f lerp(sf::Vector2f from, sf::Vector2f to, float t);
    void update(sf::Vector2f mousePosition, float delta);

private:
    bool clicked;
    sf::CircleShape ball_PRIVATE;
    float x_PRIVATE, y_PRIVATE, speed_PRIVATE;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // BALL_H
