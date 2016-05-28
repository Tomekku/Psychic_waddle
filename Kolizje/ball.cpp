#include "ball.h"


Ball::Ball()
{
    x_PRIVATE = 10;
    y_PRIVATE = 570;
    radius_PRIVATE = 5;
    ball_PRIVATE.setRadius(radius_PRIVATE);
    ball_PRIVATE.setOutlineColor(sf::Color::Blue);
    ball_PRIVATE.setFillColor(sf::Color::White);
    ball_PRIVATE.setOutlineThickness(5);
    ball_PRIVATE.setOrigin(5,5);
    ball_PRIVATE.setPosition(x_PRIVATE,y_PRIVATE);
    speed_PRIVATE = 30;
    direction = S;

}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(ball_PRIVATE);
}

sf::Vector2f Ball::setVectorByDirection(Ball::Direction direction)
{
    sf::Vector2f result;
    switch(direction)
    {
    case L:
        result.x = ball_PRIVATE.getPosition().x - speed_PRIVATE;
        result.y = ball_PRIVATE.getPosition().y;
        break;
    case T:
        result.x = ball_PRIVATE.getPosition().x;
        result.y = ball_PRIVATE.getPosition().y - speed_PRIVATE;
        break;
    case R:
        result.x = ball_PRIVATE.getPosition().x + speed_PRIVATE;
        result.y = ball_PRIVATE.getPosition().y;
        break;
    case B:
        result.x = ball_PRIVATE.getPosition().x;
        result.y = ball_PRIVATE.getPosition().y + speed_PRIVATE;
        break;
    default:
        result.x = ball_PRIVATE.getPosition().x;
        result.y = ball_PRIVATE.getPosition().y;
        break;
    }
    return result;
}

void Ball::update(Direction direction,float delta, bool collision)
{
    sf::Vector2f nextPos = setVectorByDirection(direction);
    sf::Vector2f offset = lerp(ball_PRIVATE.getPosition() ,nextPos,delta*speed_PRIVATE);

    if(!(ball_PRIVATE.getPosition().x <= 775 && ball_PRIVATE.getPosition().x >= 24 && collision) ||
            !(ball_PRIVATE.getPosition().y <= 575 && ball_PRIVATE.getPosition().y >= 24 && collision))
    {
        if((ball_PRIVATE.getPosition().x >= 0 && ball_PRIVATE.getPosition().x <=24 &&
           ball_PRIVATE.getPosition().y <= 575 && ball_PRIVATE.getPosition().y >= 525) ||
           (ball_PRIVATE.getPosition().x >=750 && ball_PRIVATE.getPosition().x <= 800 &&
            ball_PRIVATE.getPosition().y >= 0 && ball_PRIVATE.getPosition().y <= 24))
            ball_PRIVATE.move(offset);
        else
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
        offset = sf::Vector2f(to.x - from.x,to.y - from.y);




    float length = sqrtf(offset.x * offset.x + offset.y*offset.y);


    offset = sf::Vector2f(offset.x / length, offset.y / length);

    offset.x *= t;
    offset.y *= t;

    return offset;
}

