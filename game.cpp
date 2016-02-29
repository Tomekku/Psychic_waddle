#include "game.h"

Game::Game(RenderWindow &win)
{
    window_PRIVATE = &win;
    clock.restart();
    delta = 0;
}

void Game::runGame()
{
    Event event;
    bool end = false;
    while(!end)
    {
        while(window_PRIVATE->pollEvent(event))
        {
            if(Keyboard::isKeyPressed(Keyboard::Escape) && (!isCollisionExist()))
                end = true;
            if(Mouse::isButtonPressed(Mouse::Left))
                onClick();
            if(event.type == Event::Closed)
                            end = true;
        }
        update();
    }
}

bool Game::isCollisionExist()
{
    return true;
}
bool Game::isAbleToDraw()
{
    return true;
}

void Game::update()
{
    play_PRIVATE();
    player.update(sf::Vector2f(mouseX_PRIVATE, mouseY_PRIVATE),delta);
    delta = clock.getElapsedTime().asSeconds();
    clock.restart();
}

void Game::play_PRIVATE()
{
    window_PRIVATE->clear();
    //window_PRIVATE->draw(blocks);
    window_PRIVATE->draw(player);
    window_PRIVATE->display();

}

void Game::onClick()
{
    mouseX_PRIVATE = Mouse::getPosition(*window_PRIVATE).x;
    mouseY_PRIVATE = Mouse::getPosition(*window_PRIVATE).y;
    player.isClicked(true);
    //blocks.addBlock();
}
