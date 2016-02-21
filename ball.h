#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball: public Drawable, Transformable
{
public:

    Ball();
    enum Direction {L,R,T,B,LT,LB,RT,RB};    //LEFT, RIGHT, TOP, BOTTOM, LTOP, LBOTTOM, RTOP, RBOTTOM
    Direction direction;

    void update(Direction direct);
    void movement(Direction direct);

private:
    CircleShape ball_PRIVATE;
    float x_PRIVATE, y_PRIVATE, speed_PRIVATE;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // BALL_H
