#include "ball.h"


Ball::Ball()
{
    ball_PRIVATE.setRadius(25);
    ball_PRIVATE.setOutlineColor(sf::Color::Blue);
    ball_PRIVATE.setFillColor(sf::Color::White);
    ball_PRIVATE.setOutlineThickness(5);
    ball_PRIVATE.setOrigin(75,75);
    ball_PRIVATE.setPosition(350,350);
    x_PRIVATE = 350;
    y_PRIVATE = 350;
    speed_PRIVATE = 75;
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
    if(!(ball_PRIVATE.getPosition().x <= 830 && ball_PRIVATE.getPosition().x >= 70 && clicked))
    {
       offset.x *= -1;
       offset.y *= -1;
       clicked = false;
    }
    if(!(ball_PRIVATE.getPosition().y <= 630 && ball_PRIVATE.getPosition().y >= 70 && clicked))
    {
           offset.x *= -1;
           offset.y *= 1;
           clicked = false;
        }
    std::cout<<delta<<std::endl;
    ball_PRIVATE.move(offset);
}

void Ball::isClicked(bool check)
{
    if(check)
        clicked = true;
}
sf::Vector2f Ball::lerp(sf::Vector2f from, sf::Vector2f to, float t)
{
    if(from == to) return sf::Vector2f(0,0);

    sf::Vector2f offset = sf::Vector2f(to.x - from.x, to.y - from.y);
    float length = sqrtf(offset.x * offset.x + offset.y*offset.y);


    offset = sf::Vector2f(offset.x / length, offset.y / length);

    offset.x *= t;
    offset.y *= t;

    return offset;
}
