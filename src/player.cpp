#include "player.h"


Player::Player()
{
    _playerPosition = Vector2f(10,570);
    _playerRadius = 5;
    _player.setRadius(_playerRadius);
    _player.setOutlineColor(Color::Blue);
    _player.setFillColor(Color::White);
    _player.setOutlineThickness(5);
    _player.setOrigin(5,5);
    _player.setPosition(_playerPosition);
    _playerSpeed = 30;
    _playerDirection = STOP;

}

void Player::draw(RenderTarget &target, RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_player);
}

Vector2f Player::setVectorByDirection(Player::Direction direction)
{
    Vector2f result;
    switch(direction)
    {
    case LEFT:
        result.x = _player.getPosition().x - _playerSpeed;
        result.y = _player.getPosition().y;
        break;
    case TOP:
        result.x = _player.getPosition().x;
        result.y = _player.getPosition().y - _playerSpeed;
        break;
    case RIGHT:
        result.x = _player.getPosition().x + _playerSpeed;
        result.y = _player.getPosition().y;
        break;
    case BOTTOM:
        result.x = _player.getPosition().x;
        result.y = _player.getPosition().y + _playerSpeed;
        break;
    default:
        result.x = _player.getPosition().x;
        result.y = _player.getPosition().y;
        break;
    }
    return result;
}

bool Player::playerUpdate(Direction direction,float timeDelta, bool collision)
{
    Vector2f nextPos = setVectorByDirection(direction);
    Vector2f offset = createOffset(_player.getPosition(), nextPos, timeDelta*_playerSpeed);

    if(!(_player.getPosition().x <= 775 && _player.getPosition().x >= 24 && collision) ||
            !(_player.getPosition().y <= 575 && _player.getPosition().y >= 24 && collision))
    {
        if((_player.getPosition().x >= 0 && _player.getPosition().x <=24 &&
           _player.getPosition().y <= 575 && _player.getPosition().y >= 565) ||
           (_player.getPosition().x >=765 && _player.getPosition().x <= 775 &&
            _player.getPosition().y >= 0 && _player.getPosition().y <= 24))
        {

            _player.move(offset);
            return true;
        }
        else
        {
            if(_player.getPosition().x >=750 && _player.getPosition().x <= 800 && _player.getPosition().y <= 0)
                std::cout<<"winner!!!!!!!!!!!!!!!!!!"<<std::endl;
            else
            std::cout<<"crashed!!!!"<<std::endl;
            _player.setPosition(_playerPosition);
            return false;
        }
    }
    else
    {
        _player.move(offset);
        return true;
    }
    //std::cout<<delta<<std::endl;

}

Vector2f Player::createOffset(Vector2f from, Vector2f to, float distance)
{
    if(from == to) return Vector2f(0,0);

    Vector2f offset;
    offset = Vector2f(to.x - from.x,to.y - from.y);

    float length = sqrtf(offset.x * offset.x + offset.y*offset.y);


    offset = Vector2f(offset.x / length, offset.y / length);

    offset.x *= distance;
    offset.y *= distance;

    return offset;
}

