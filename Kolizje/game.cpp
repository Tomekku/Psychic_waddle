#include "game.h"

Game::Game(RenderWindow &win)
{
    window_PRIVATE = &win;
    clock.restart();
    delta = 0;
    state = END;
    if(!font.loadFromFile("mecha.ttf"))
        return ;
    state = MENU;
    direction_PRIVATE = player.getDir();
}

void Game::runGame()
{
    while(state != END)
    {
        switch(state)
        {
        case MENU:
            menu();
            break;
        case LEVEL:
            level();
            break;
        case LOADING:
            loading();
            break;
        }
    }
}

bool Game::isCollisionNotExist()
{
    bool result = true;
    for(unsigned int i=0;i<Maze_PRIVATE.MazeContainer.size();i++)
    {
        Vector2f topLeft, topRight, botLeft, botRight, playerCoords;
        float distance[4];
        playerCoords.x = player.getPos().x;
        playerCoords.y = player.getPos().y;

        topLeft.x = Maze_PRIVATE.MazeContainer.at(i).getPosition().x;
        topLeft.y = Maze_PRIVATE.MazeContainer.at(i).getPosition().y;

        topRight.x = Maze_PRIVATE.MazeContainer.at(i).getPosition().x + Maze_PRIVATE.MazeContainer.at(i).getSize().x;
        topRight.y = Maze_PRIVATE.MazeContainer.at(i).getPosition().y;

        botLeft.x = Maze_PRIVATE.MazeContainer.at(i).getPosition().x;
        botLeft.y = Maze_PRIVATE.MazeContainer.at(i).getPosition().y + Maze_PRIVATE.MazeContainer.at(i).getSize().y;

        botRight.x = Maze_PRIVATE.MazeContainer.at(i).getPosition().x + Maze_PRIVATE.MazeContainer.at(i).getSize().x;
        botRight.y = Maze_PRIVATE.MazeContainer.at(i).getPosition().y + Maze_PRIVATE.MazeContainer.at(i).getSize().y;

        distance[0] = sqrtf(pow(playerCoords.x - topLeft.x,2) + pow(playerCoords.y - topLeft.y,2));
        distance[1] = sqrtf(pow(playerCoords.x - topRight.y,2) + pow(playerCoords.y - topRight.y,2));
        distance[2] = sqrtf(pow(playerCoords.x - botLeft.x,2) + pow(playerCoords.y - botLeft.y,2));
        distance[3] = sqrtf(pow(playerCoords.x - botRight.x,2) + pow(playerCoords.y - botRight.y,2));



        for(int j=0;j<4;j++) ///TODO: conditions to collide with walls between topLeft, topRight, botLeft, botRight
        {
            if(distance[j] <= player.getRadius()+2*player.getThickness()+2 || (playerCoords.x >= topLeft.x && playerCoords.x <= topRight.x && playerCoords.y <=topLeft.x && playerCoords.y >= botLeft.y))
            {
                std::cout<<"crashed z: kwadrat-"<<i<<" róg-"<<j<<std::endl;
                result = false;
            }
        }

    }
    return result;
}

void Game::createValidMaze()
{

    Maze_PRIVATE.createMaze();
    for(unsigned int i=0;i<Maze_PRIVATE.MazeContainer.size();i++)
    {
        if((Maze_PRIVATE.MazeContainer.at(i).getPosition().x == 742 && Maze_PRIVATE.MazeContainer.at(i).getPosition().y == 20) ||
            (Maze_PRIVATE.MazeContainer.at(i).getPosition().x == 20 && Maze_PRIVATE.MazeContainer.at(i).getPosition().y == 552))
        {
            Maze_PRIVATE.MazeContainer.erase(Maze_PRIVATE.MazeContainer.begin()+i);
           // std::cout<<"usunieto!!!!!!"<<std::endl;
        }
        //std::cout<<"X: "<<Maze_PRIVATE.MazeContainer.at(i).getPosition().x<<" Y: "<<Maze_PRIVATE.MazeContainer.at(i).getPosition().y<<std::endl;
    }
}

bool Game::isAbleToDraw()
{
    Maze_PRIVATE.clearContainers();
    state = LOADING;
    while(state == LOADING)
    {
        srand(time(NULL));
        loading();
        createValidMaze();
        blocks.addBlock(800,10,0,590);
        blocks.addBlock(750,10,0,0);

        blocks.addBlock(10,550,0,0);
        blocks.addBlock(10,600,790,0);
        state = LEVEL;
    }
    return true;
}

void Game::update()
{
    play_PRIVATE();
    player.update(direction_PRIVATE,delta, isCollisionNotExist());
    delta = clock.getElapsedTime().asSeconds();
    clock.restart();
}

void Game::play_PRIVATE()
{
    window_PRIVATE->clear();
    window_PRIVATE->draw(blocks);
    window_PRIVATE->draw(Maze_PRIVATE);
    window_PRIVATE->draw(player);
    window_PRIVATE->display();

}

void Game::menu()
{
    Text title("Physic Waddle",font,80);
    title.setStyle(Text::Bold);
    direction_PRIVATE = Ball::S;
    title.setPosition(800/2-title.getGlobalBounds().width/2,20);

    const int textsCount = 3;

    Text text[textsCount];
    std::string str[textsCount];
    if(Maze_PRIVATE.MazeContainer.size() != 0)
    {

        str[0] = "Play";
        str[1] = "Next maze";
        str[2] = "Exit";
    }
    else
    {
        str[0] = "Play";
        str[1] = "---------";
        str[2] = "Exit";
    }
    for(int i=0;i<textsCount;i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize(65);

        text[i].setString(str[i]);
        text[i].setPosition(800/2-text[i].getGlobalBounds().width/2,150+i*120);
    }

    while(state == MENU)
    {
        Vector2f mouse(Mouse::getPosition(*window_PRIVATE));
        Event event;


        while(window_PRIVATE->pollEvent(event))
        {
            //Wciniêcie ESC lub przycisk X
            if(event.type == Event::Closed || (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::Escape))
            {
                state = END;
            }
            //kliknięcie Menu
            if(text[0].getGlobalBounds().contains(mouse) &&
                    event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
            {
                if(Maze_PRIVATE.MazeContainer.size() == 0)
                    isAbleToDraw();
                else
                    state = LEVEL;
            }
            //klikniêcie Next Maze
            if(text[1].getGlobalBounds().contains(mouse) &&
                event.type == Event::MouseButtonReleased && (event.key.code == Mouse::Left || event.key.code == Mouse::Right))
                isAbleToDraw();
            //klikniêcie EXIT
            else if(text[2].getGlobalBounds().contains(mouse) &&
                event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
            {
                state = END;
            }
        }
        for(int i=0;i<textsCount;i++)
            if(text[i].getGlobalBounds().contains(mouse))
                text[i].setColor(Color::Cyan);
            else text[i].setColor(Color::White);

        window_PRIVATE->clear();

        window_PRIVATE->draw(title);
        for(int i=0;i<textsCount;i++)
            window_PRIVATE->draw(text[i]);

        window_PRIVATE->display();
    }
}

void Game::level()                                                                                  //TODO: generowanie losowego labiryntu
{
    Event event;
    while(state == LOADING)
        loading();
            while(state == LEVEL)
        {
            while(window_PRIVATE->pollEvent(event))
            {
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::Escape)
                    state = MENU;
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::A)
                    direction_PRIVATE = Ball::L;
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::D)
                    direction_PRIVATE = Ball::R;
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::W)
                    direction_PRIVATE = Ball::T;
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::S)
                    direction_PRIVATE = Ball::B;


                if(event.type == Event::Closed)
                    state = END;
            }
            update();
        }
}

void Game::loading()
{
    Text title("Loading",font,80);
    title.setStyle(Text::Bold);

    title.setPosition(800/2-title.getGlobalBounds().width/2,20);
    window_PRIVATE->clear();
    window_PRIVATE->draw(title);
    window_PRIVATE->display();
}
