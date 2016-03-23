#include "block.h"

Block::Block()
{

}

void Block::addBlock(float tmp_size_x, float tmp_size_y, float tmp_pos_x, float tmp_pos_y)
{
    currBlock_PRIVATE.setSize(Vector2f(tmp_size_x,tmp_size_y));
    currBlock_PRIVATE.setFillColor(Color::Red);
    currBlock_PRIVATE.setOutlineColor(Color::Red);
    currBlock_PRIVATE.setOutlineThickness(5);
    currBlock_PRIVATE.setPosition(Vector2f(tmp_pos_x,tmp_pos_y));
    blockContainer.push_back(currBlock_PRIVATE);
}

void Block::draw(RenderTarget &target, RenderStates states) const
{
    //states.transform *= getTransform();
    for(unsigned int i=0;i<blockContainer.size();i++)
        target.draw(blockContainer[i]);
}
