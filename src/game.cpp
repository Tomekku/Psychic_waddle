#include "game.h"

Game::Game(RenderWindow &win)
{
    _window_ptr = &win;
    _clock.restart();
    _timeDelta = 0;
    _gameState = END;
    if(!_font.loadFromFile("mecha.ttf"))
        return ;
    _gameState = MENU;
    _playerDirection = _player.getPlayerDirection();
}

void Game::runGame()
{
    while(_gameState != END)
    {
        switch(_gameState)
        {
        case MENU:
            _loadMenu();
            break;
        case LEVEL:
            _loadLevel();
            break;
        case LOADING:
            _loading();
            break;
        }
    }
}

bool Game::_isCollisionNotExist()
{
    bool result = true;
    Vector2f topLeft, topRight, botLeft, botRight, playerCoords;
    float distance[4];
    playerCoords.x = _player.getPlayerPosition().x;
    playerCoords.y = _player.getPlayerPosition().y;
    for(unsigned int i=0;i<_mazeGenerator.MazeContainer.size();i++)
    {
        topLeft.x = _mazeGenerator.MazeContainer.at(i).getPosition().x;
        topLeft.y = _mazeGenerator.MazeContainer.at(i).getPosition().y;

        topRight.x = _mazeGenerator.MazeContainer.at(i).getPosition().x + _mazeGenerator.MazeContainer.at(i).getSize().x;
        topRight.y = _mazeGenerator.MazeContainer.at(i).getPosition().y;

        botLeft.x = _mazeGenerator.MazeContainer.at(i).getPosition().x;
        botLeft.y = _mazeGenerator.MazeContainer.at(i).getPosition().y + _mazeGenerator.MazeContainer.at(i).getSize().y;

        botRight.x = _mazeGenerator.MazeContainer.at(i).getPosition().x + _mazeGenerator.MazeContainer.at(i).getSize().x;
        botRight.y = _mazeGenerator.MazeContainer.at(i).getPosition().y + _mazeGenerator.MazeContainer.at(i).getSize().y;

        for(int p=0;p<=_mazeGenerator.MazeContainer.at(i).getSize().x;p++)
        {
            distance[0] = sqrtf(pow(playerCoords.x - (topLeft.x + p),2) + pow(playerCoords.y - topLeft.y,2));
            distance[1] = sqrtf(pow(playerCoords.x - (botLeft.x + p),2) + pow(playerCoords.y - botLeft.y,2));
            if(distance[0] <= _player.getPlayerRadius()+2*_player.getPlayerThickness() || distance[1] <= _player.getPlayerRadius()+2*_player.getPlayerThickness())
            {
                //std::cout<<"crashed z góra - kwadrat: "<<i<<" punkt: "<<p<<std::endl;
                result = false;
            }
        }
        for(int p=0;p<=_mazeGenerator.MazeContainer.at(i).getSize().y;p++)
        {
            distance[2] = sqrtf(pow(playerCoords.x - topLeft.x,2) + pow(playerCoords.y - (topLeft.y + p),2));
            distance[3] = sqrtf(pow(playerCoords.x - topRight.x,2) + pow(playerCoords.y - (topLeft.y + p),2));
            if(distance[2] <= _player.getPlayerRadius()+2*_player.getPlayerThickness() || distance[2] <= _player.getPlayerRadius()+2*_player.getPlayerThickness())
            {
                //std::cout<<"crashed z lewo - kwadrat: "<<i<<" punkt: "<<p<<std::endl;
                result = false;
            }
        }
    }
    return result;
}

void Game::_createValidMaze()
{

    _mazeGenerator.createMaze();
    for(unsigned int i=0;i<_mazeGenerator.MazeContainer.size();i++)
    {
        if((_mazeGenerator.MazeContainer.at(i).getPosition().x == 742 && _mazeGenerator.MazeContainer.at(i).getPosition().y == 20) ||
            (_mazeGenerator.MazeContainer.at(i).getPosition().x == 20 && _mazeGenerator.MazeContainer.at(i).getPosition().y == 552) ||
             (_mazeGenerator.MazeContainer.at(i).getPosition().x == 58 && _mazeGenerator.MazeContainer.at(i).getPosition().y == 552) ||
             (_mazeGenerator.MazeContainer.at(i).getPosition().x == 20 && _mazeGenerator.MazeContainer.at(i).getPosition().y == 514) ||
             (_mazeGenerator.MazeContainer.at(i).getPosition().x == 58 && _mazeGenerator.MazeContainer.at(i).getPosition().y == 514) ||
             (_mazeGenerator.MazeContainer.at(i).getPosition().x == 704 && _mazeGenerator.MazeContainer.at(i).getPosition().y == 20) ||
             (_mazeGenerator.MazeContainer.at(i).getPosition().x == 742 && _mazeGenerator.MazeContainer.at(i).getPosition().y == 58))
        {
            _mazeGenerator.MazeContainer.erase(_mazeGenerator.MazeContainer.begin()+i);
            i--;
           // std::cout<<"usunieto!!!!!!"<<std::endl;
        }
        std::cout<<"X: "<<_mazeGenerator.MazeContainer.at(i).getPosition().x<<" Y: "<<_mazeGenerator.MazeContainer.at(i).getPosition().y<<std::endl;
    }

}

bool Game::_isAbleToDraw()
{
    _mazeGenerator.clearContainers();
    _gameState = LOADING;
    while(_gameState == LOADING)
    {
        srand(time(NULL));
        _loading();
        _createValidMaze();
        _createMazeBorders();
        _gameState = LEVEL;
    }
    return true;
}

void Game::_createMazeBorders()
{
    Vector2f topBorderSize(750,10), bottomBorderSize(800,10), leftBorderSize(10,550), rightBorderSize(10,600);
    Vector2f topBorderPosition(0,0), bottomBorderPosition(0,590), leftBorderPosition(0,0), rightBorderPosition(790,0);

    _blocks.addBlock(bottomBorderSize,bottomBorderPosition);
    _blocks.addBlock(topBorderSize,topBorderPosition);
    _blocks.addBlock(leftBorderSize,leftBorderPosition);
    _blocks.addBlock(rightBorderSize,rightBorderPosition);
}

void Game::_update()
{
    _prepareWindow();
    if(!_player.playerUpdate(_playerDirection,_timeDelta, _isCollisionNotExist()))
    {
        _mazeGenerator.clearContainers();
        _gameState = MENU;
    }
    _timeDelta = _clock.getElapsedTime().asSeconds();
    _clock.restart();
}

void Game::_prepareWindow()
{
    _window_ptr->clear();
    _window_ptr->draw(_blocks);
    _window_ptr->draw(_mazeGenerator);
    _window_ptr->draw(_player);
    _window_ptr->display();

}

void Game::_loadMenu()
{
    Text title("Physic Waddle",_font,80);
    title.setStyle(Text::Bold);
    _playerDirection = Player::STOP;
    title.setPosition(800/2-title.getGlobalBounds().width/2,20);

    const int textsCount = 3;

    Text text[textsCount];
    std::string str[textsCount];
    if(_mazeGenerator.MazeContainer.size() != 0)
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
        text[i].setFont(_font);
        text[i].setCharacterSize(65);

        text[i].setString(str[i]);
        text[i].setPosition(800/2-text[i].getGlobalBounds().width/2,150+i*120);
    }

    while(_gameState == MENU)
    {
        Vector2f mouse(Mouse::getPosition(*_window_ptr));
        Event event;


        while(_window_ptr->pollEvent(event))
        {
            //Wciniêcie ESC lub przycisk X
            if(event.type == Event::Closed || (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::Escape))
            {
                _gameState = END;
            }
            //kliknięcie Menu
            if(text[0].getGlobalBounds().contains(mouse) &&
                    event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
            {
                if(_mazeGenerator.MazeContainer.size() == 0)
                    _isAbleToDraw();
                else
                    _gameState = LEVEL;
            }
            //klikniêcie Next Maze
            if(text[1].getGlobalBounds().contains(mouse) &&
                event.type == Event::MouseButtonReleased && (event.key.code == Mouse::Left || event.key.code == Mouse::Right))
                _isAbleToDraw();
            //klikniêcie EXIT
            else if(text[2].getGlobalBounds().contains(mouse) &&
                event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
            {
                _gameState = END;
            }
        }
        for(int i=0;i<textsCount;i++)
            if(text[i].getGlobalBounds().contains(mouse))
                text[i].setColor(Color::Cyan);
            else text[i].setColor(Color::White);

        _window_ptr->clear();

        _window_ptr->draw(title);
        for(int i=0;i<textsCount;i++)
            _window_ptr->draw(text[i]);

        _window_ptr->display();
    }
}

void Game::_loadLevel()                                                                                  //TODO: generowanie losowego labiryntu
{
    Event event;
    while(_gameState == LOADING)
        _loading();
            while(_gameState == LEVEL)
        {
            while(_window_ptr->pollEvent(event))
            {
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::Escape)
                    _gameState = MENU;
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::A)
                    _playerDirection = Player::LEFT;
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::D)
                    _playerDirection = Player::RIGHT;
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::W)
                    _playerDirection = Player::TOP;
                if(event.type == Event::KeyPressed &&
                        event.key.code == Keyboard::S)
                    _playerDirection = Player::BOTTOM;


                if(event.type == Event::Closed)
                    _gameState = END;
            }
            _update();
            std::cout<<"X: "<<_player.getPlayerPosition().x<<" Y: "<<_player.getPlayerPosition().y<<std::endl;
        }
}

void Game::_loading()
{
    Text title("Loading",_font,80);
    title.setStyle(Text::Bold);

    title.setPosition(800/2-title.getGlobalBounds().width/2,20);
    _window_ptr->clear();
    _window_ptr->draw(title);
    _window_ptr->display();
}
