#include "ball.h"


Ball::Ball()
{
    x_PRIVATE = 400;
    y_PRIVATE = 500;
    ball_PRIVATE.setRadius(5);
    ball_PRIVATE.setOutlineColor(sf::Color::Blue);
    ball_PRIVATE.setFillColor(sf::Color::White);
    ball_PRIVATE.setOutlineThickness(5);
    ball_PRIVATE.setOrigin(77,77);
    ball_PRIVATE.setPosition(x_PRIVATE,y_PRIVATE);
    speed_PRIVATE = 30;
    direction = T;
    clicked = true;

}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(ball_PRIVATE);
}

void Ball::update(sf::Vector2f mousePosition,float delta)
{
     sf::Vector2f offset= lerp(mousePosition,ball_PRIVATE.getPosition(),delta*speed_PRIVATE);

    if(!(ball_PRIVATE.getPosition().x <= 850 && ball_PRIVATE.getPosition().x >= 90 && clicked) ||
            !(ball_PRIVATE.getPosition().y <= 650 && ball_PRIVATE.getPosition().y >= 90 && clicked))
    {
       std::cout<<"crashed!!!!"<<std::endl;
    }
    else
        ball_PRIVATE.move(offset);
    //std::cout<<delta<<std::endl;

}

sf::Vector2f Ball::lerp(sf::Vector2f from, sf::Vector2f to, float t)
{
    if(from == to) return sf::Vector2f(0,0);

    sf::Vector2f offset;
        offset = sf::Vector2f(to.x - from.x, from.y - to.y);




    float length = sqrtf(offset.x * offset.x + offset.y*offset.y);


    offset = sf::Vector2f(offset.x / length, offset.y / length);

    offset.x *= t;
    offset.y *= t;

    return offset;
}
