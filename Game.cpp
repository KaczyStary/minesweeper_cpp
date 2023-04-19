#include "Game.h"

Game::Game() {
    this->initTextures();
    this->initVariables();
    this->initWindow();

    this->gameLoop();
}

void Game::initWindow() {
    this->windowBounds.width=this->windowWidth;
    this->windowBounds.height=this->windowHeight;
    this->window=new sf::RenderWindow((this->windowBounds), this->windowName);
}

void Game::initVariables() {
    this->windowHeight=480;
    this->windowWidth=720;
    this->windowBounds=sf::VideoMode::getDesktopMode();
    this->windowName="Minesweeper";
}

void Game::initTextures() {
    for (int i = 0; i < 19; ++i) {
        std::string filename = "C:/Users/huber/CLionProjects/minesweeper_ff/Resources/" + std::to_string(i) + ".png";
        texture.loadFromFile(filename);
        textures.push_back(texture);
    }
}

void Game::gameLoop() {

    MinesweeperBoard minesweeperBoard;
    windowSwitchWindowToGame();

    while (this->window->isOpen()){
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);


        this->windowClose();

        if (sfEvent.type == sf::Event::MouseButtonPressed) {
            if (sfEvent.mouseButton.button == sf::Mouse::Left) {
                std::cout<<mousePos.y<<" + "<<mousePos.x<<"\n";
                leftClick = true;

            } else if (sfEvent.mouseButton.button == sf::Mouse::Right) {
                std::cout<<mousePos.y<<" + "<<mousePos.x<<"\n";
                rightClick = true;
            }
        }

        if (sfEvent.type == sf::Event::MouseButtonReleased) {
            if (sfEvent.mouseButton.button == sf::Mouse::Left) {
                if (leftClick){

                    minesweeperBoard.revealFiled( mousePos.y/48, mousePos.x/48 );
                    minesweeperBoard.debugDisplay();

                    leftClick= false;
                }

            } else if (sfEvent.mouseButton.button == sf::Mouse::Right) {
                if (rightClick){

                    minesweeperBoard.toggleFlag( mousePos.y/48, mousePos.x/48 );
                    minesweeperBoard.debugDisplay();

                    rightClick= false;
                }
            }
        }

        //this->render();

        this->window->clear();


        int scale=4;
        int x=0;
        int y=0;

        for (int i = 0; i < MinesweeperBoard().boardHeight; i++) {
            for (int j = 0; j < MinesweeperBoard().boardWidth; j++) {

                this->sprite.setTexture(textures[setTextures(i,j)]);
                this->sprite.setScale(scale,scale);
                sprite.setPosition(x*scale,y*scale);

                this->window->draw(sprite);
                y+=12;
            }
            y=0;
            x+=12;
        }

        this->window->display();

    }

}

void Game::windowClose() {
        while (this->window->pollEvent(this->sfEvent)){
        if (sfEvent.type==sf::Event::Closed){
            this->window->close();
        }
    }
}

void Game::initGame() {
    MinesweeperBoard minesweeperBoard;
    minesweeperBoard.debugDisplay();

    windowSwitchWindowToGame();

}

void Game::windowSwitchWindowToGame() {
    delete this->window;

    this->windowBounds.width=MinesweeperBoard().boardWidth*48;
    this->windowBounds.height=MinesweeperBoard().boardHeight*48;

    this->window=new sf::RenderWindow((this->windowBounds), this->windowName);
}

void Game::inGameRender() {
    int scale=4;
    int x=0;
    int y=0;

    for (int i = 0; i < MinesweeperBoard().boardHeight; i++) {
        for (int j = 0; j < MinesweeperBoard().boardWidth; j++) {

            this->sprite.setTexture(textures[setTextures(i,j)]);
            this->sprite.setScale(scale,scale);
            sprite.setPosition(x*scale,y*scale);

            this->window->draw(sprite);
            y+=12;
        }
        y=0;
        x+=12;
    }
}

void Game::render(){
    this->window->clear();

    inGameRender();

    this->window->display();
}

int Game::setTextures(MinesweeperBoard *minesweeperBoard, int height, int width) {
    int numText=0;

    // NIE ODKRYTE, BEZ MINY, BEZ FLAGI - MOZLIWE
    if (!minesweeperBoard->boardVector[height][width].isRevealed && !MinesweeperBoard().boardVector[height][width].hasMine && !MinesweeperBoard().boardVector[height][width].hasFlag){
        numText=12;
    }
        // NIE ODKRYTE, BEZ MINY, FLAGA - MOZLIWE
    else if (!MinesweeperBoard().boardVector[height][width].isRevealed && !MinesweeperBoard().boardVector[height][width].hasMine && MinesweeperBoard().boardVector[height][width].hasFlag){
        numText=10;
    }
        // NIE ODKRYTE, MINA, BEZ FLAGI - MOZLIWE
    else if (!MinesweeperBoard().boardVector[height][width].isRevealed && MinesweeperBoard().boardVector[height][width].hasMine && !MinesweeperBoard().boardVector[height][width].hasFlag){
        numText=13;
    }
        // NIE ODKRYTE, MINA, FLAGA - MOZLIWE
    else if (!MinesweeperBoard().boardVector[height][width].isRevealed && MinesweeperBoard().boardVector[height][width].hasMine && MinesweeperBoard().boardVector[height][width].hasFlag){
        numText=11;
    }

        // ODKRYTE, BEZ MINY, BEZ FLAGI - MOZLIWE
    else if (MinesweeperBoard().boardVector[height][width].isRevealed && !MinesweeperBoard().boardVector[height][width].hasMine && !MinesweeperBoard().boardVector[height][width].hasFlag){
        numText=MinesweeperBoard().minesAroundField(height, width);
    }
        // ODKRYTE, BEZ MINY, FLAGA - NIE MOZLIWE
    else if (MinesweeperBoard().boardVector[height][width].isRevealed && !MinesweeperBoard().boardVector[height][width].hasMine && MinesweeperBoard().boardVector[height][width].hasFlag){
        numText=15;
    }
        // ODKRYTE, MINA, BEZ FLAGI - MOZLIWE
    else if (MinesweeperBoard().boardVector[height][width].isRevealed && MinesweeperBoard().boardVector[height][width].hasMine && !MinesweeperBoard().boardVector[height][width].hasFlag){
        numText=15;
    }
        // ODKRYTE, MINA, FLAGA - NIE MOZLIWE
    else if (MinesweeperBoard().boardVector[height][width].isRevealed && MinesweeperBoard().boardVector[height][width].hasMine && MinesweeperBoard().boardVector[height][width].hasFlag){
        numText=textures.size()+1;
    }else
    {
        numText= textures.size()+1;
    }

    return numText;
}





