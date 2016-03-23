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

bool Game::isCollisionExist()
{
    return true;
}
bool Game::isAbleToDraw()
{
    state = LOADING;
    while(state == LOADING)
    {
        srand(time(NULL));
        Maze_PRIVATE.createMaze();
        blocks.addBlock(800,10,0,590);
        blocks.addBlock(800,10,0,0);

        blocks.addBlock(10,600,0,0);
        blocks.addBlock(10,600,790,0);
        state = LEVEL;
    }
    return true;
}

void Game::update()
{
    play_PRIVATE();
    player.update(Vector2f(mouseY_PRIVATE, mouseX_PRIVATE),delta);
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

void Game::onClick()
{
    mouseX_PRIVATE = Mouse::getPosition(*window_PRIVATE).x;
    mouseY_PRIVATE = Mouse::getPosition(*window_PRIVATE).y;
    //blocks.addBlock();
}

void Game::menu()
{
    Text title("Physic Waddle",font,80);
    title.setStyle(Text::Bold);

    title.setPosition(800/2-title.getGlobalBounds().width/2,20);

    const int ile = 2;

    Text tekst[ile];

    std::string str[] = {"Play","Exit"};
    for(int i=0;i<ile;i++)
    {
        tekst[i].setFont(font);
        tekst[i].setCharacterSize(65);

        tekst[i].setString(str[i]);
        tekst[i].setPosition(800/2-tekst[i].getGlobalBounds().width/2,150+i*120);
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
            //klikniêcie MENU
            if(tekst[0].getGlobalBounds().contains(mouse) &&
                event.type == Event::MouseButtonReleased && (event.key.code == Mouse::Left || event.key.code == Mouse::Right))
            {
                isAbleToDraw();
            }
            //klikniêcie EXIT
            else if(tekst[1].getGlobalBounds().contains(mouse) &&
                event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
            {
                state = END;
            }
        }
        for(int i=0;i<ile;i++)
            if(tekst[i].getGlobalBounds().contains(mouse))
                tekst[i].setColor(Color::Cyan);
            else tekst[i].setColor(Color::White);

        window_PRIVATE->clear();

        window_PRIVATE->draw(title);
        for(int i=0;i<ile;i++)
            window_PRIVATE->draw(tekst[i]);

        window_PRIVATE->display();
    }
}

void Game::level()                                                                                  //TODO: generowanie losowego labiryntu
{
    while(state == LOADING)
        loading();

        Event event;
        while(state == LEVEL)
        {
            while(window_PRIVATE->pollEvent(event))
            {
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::Escape)
                    state = MENU;
                if(Mouse::isButtonPressed(Mouse::Left))
                    onClick();
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
