#include "block.h"

Block::Block()
{

}

void Block::addBlock(Vector2f size, Vector2f position)
{
    currBlock_PRIVATE.setSize(size);
    currBlock_PRIVATE.setFillColor(Color::Red);
    currBlock_PRIVATE.setOutlineColor(Color::Red);
    currBlock_PRIVATE.setOutlineThickness(5);
    currBlock_PRIVATE.setPosition(position);
    blockContainer.push_back(currBlock_PRIVATE);
}

void Block::draw(RenderTarget &target, RenderStates states) const
{
    //states.transform *= getTransform();
    for(unsigned int i=0;i<blockContainer.size();i++)
        target.draw(blockContainer[i]);
}
