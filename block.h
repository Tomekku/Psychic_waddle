#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>
#include <iostream>
/*#include <stdlib.h>
#include <time.h>*/

using namespace sf;

class Block: public Drawable
{
public:
    Block();
    FloatRect getFloatRectOfBlock(RectangleShape rect) const;
    std::vector <RectangleShape> blockContainer;
    void addBlock(float tmp_size_x, float tmp_size_y, float tmp_pos_x, float tmp_pos_y);

private:
    RectangleShape currBlock_PRIVATE;
    virtual void draw(RenderTarget &target, RenderStates states) const;

};

#endif // BLOCK_H
