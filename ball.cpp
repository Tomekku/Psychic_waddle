#include "ball.h"


Ball::Ball()
{


}

Ball::draw(RenderTarget &target, RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(ball);
}
