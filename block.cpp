#include "block.h"

Block::Block()
{

}

void Block::addBlock()
{
    srand(time(NULL));
    float tmp_size_x = rand()%200+50, tmp_size_y = rand()%200+50,
            tmp_x = rand()%600, tmp_y = rand()%400;
    for(unsigned int i=0;i<blockContainer.size();i++)
    {
        while(Vector2f(tmp_size_x,tmp_size_y) == blockContainer[i].getSize() && Vector2f(tmp_x,tmp_y) == blockContainer[i].getPosition())
        {
            std::cout<<"chleb"<<std::endl;
            srand(time(NULL));
            tmp_size_x = rand()%200+50; tmp_size_y = rand()%200+50;
            tmp_x = rand()%600; tmp_y = rand()%400;
        }
    }

    currBlock_PRIVATE.setSize(Vector2f(tmp_size_x,tmp_size_y));
    currBlock_PRIVATE.setFillColor(Color::White);
    currBlock_PRIVATE.setOutlineColor(Color::Red);
    currBlock_PRIVATE.setOutlineThickness(5);
    currBlock_PRIVATE.setPosition(Vector2f(tmp_x,tmp_y));
    blockContainer.push_back(currBlock_PRIVATE);
}

void Block::draw(RenderTarget &target, RenderStates states) const
{
    //states.transform *= getTransform();
    for(unsigned int i=0;i<blockContainer.size();i++)
        target.draw(blockContainer[i]);
}
