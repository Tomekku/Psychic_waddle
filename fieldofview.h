#ifndef FIELDOFVIEW_H
#define FIELDOFVIEW_H
#include <SFML/Graphics.hpp>
#include "ball.h"

using namespace sf;

class FieldOfView
{
public:
    FieldOfView();
    void update();
    void move(Ball::Direction direct);

private:
    CircleShape field_PRIVATE;
    Ball::Direction direction_PRIVATE;
};

#endif // FIELDOFVIEW_H
