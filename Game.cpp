#include "Game.h"

void Game::changeStateToLose(){
    gameState=GAMELOST;
}

void Game::changeStateToWin() {
    gameState=GAMEWIN;
}

void Game::changeStateToStart() {
    gameState=GAMESTART;
    windowSwitchWindowToGame();
}

void Game::changeStateToMenu() {
    gameState=GAMEMENU;
}

void Game::changeStateToContinue() {
    gameState=GAMECONTINUE;
}

int Game::setTextures(int height, int width) {
    int numText=0;

    // NIE ODKRYTE, BEZ MINY, BEZ FLAGI - MOZLIWE
    if (!minesweeperBoard.boardVector[height][width].isRevealed && !minesweeperBoard.boardVector[height][width].hasMine && !minesweeperBoard.boardVector[height][width].hasFlag){
        numText=12;
    }
        // NIE ODKRYTE, BEZ MINY, FLAGA - MOZLIWE
    else if (!minesweeperBoard.boardVector[height][width].isRevealed && !minesweeperBoard.boardVector[height][width].hasMine && minesweeperBoard.boardVector[height][width].hasFlag){
        numText=10;
    }
        // NIE ODKRYTE, MINA, BEZ FLAGI - MOZLIWE
    else if (!minesweeperBoard.boardVector[height][width].isRevealed && minesweeperBoard.boardVector[height][width].hasMine && !minesweeperBoard.boardVector[height][width].hasFlag){
        numText=13;
    }
        // NIE ODKRYTE, MINA, FLAGA - MOZLIWE
    else if (!minesweeperBoard.boardVector[height][width].isRevealed && minesweeperBoard.boardVector[height][width].hasMine && minesweeperBoard.boardVector[height][width].hasFlag){
        numText=11;
    }

        // ODKRYTE, BEZ MINY, BEZ FLAGI - MOZLIWE
    else if (minesweeperBoard.boardVector[height][width].isRevealed && !minesweeperBoard.boardVector[height][width].hasMine && !minesweeperBoard.boardVector[height][width].hasFlag){
        numText=minesweeperBoard.minesAroundField(height, width);
    }
        // ODKRYTE, BEZ MINY, FLAGA - NIE MOZLIWE
    else if (minesweeperBoard.boardVector[height][width].isRevealed && !minesweeperBoard.boardVector[height][width].hasMine && minesweeperBoard.boardVector[height][width].hasFlag){
        numText=15;
    }
        // ODKRYTE, MINA, BEZ FLAGI - MOZLIWE
    else if (minesweeperBoard.boardVector[height][width].isRevealed && minesweeperBoard.boardVector[height][width].hasMine && !minesweeperBoard.boardVector[height][width].hasFlag){
        numText=15;
    }
        // ODKRYTE, MINA, FLAGA - NIE MOZLIWE
    else if (minesweeperBoard.boardVector[height][width].isRevealed && minesweeperBoard.boardVector[height][width].hasMine && minesweeperBoard.boardVector[height][width].hasFlag){
        numText=textures.size()+1;
    }else
    {
        numText= textures.size()+1;
    }

    return numText;
}

Game::Game() {

    //ZROBIC REFAKTORYZACJE OBIEKTU MINESWEEPERBOARD, TAK, ZEBY DO KONSTRUKTORA
    // PRZYJMOWAL WYMIARY PLANSZY, POZIOM TRUDNOSCI
    // ZROBIC TEZ TAK, ZEBY DODAWAC I USUWAC OBIEKT MINESWEEPERBOAR

    this->initTextures();
    this->initVariables();
    this->initState();
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

void Game::initState(){
    changeStateToMenu();
}

void Game::initTextures() {
    for (int i = 0; i < 19; ++i) {
        std::string filename = "C:/Users/huber/CLionProjects/minesweeper_ff/Resources/" + std::to_string(i) + ".png";
        texture.loadFromFile(filename);
        textures.push_back(texture);
    }
}

void Game::trackMouse() {
    mouseInput.mousePos=sf::Mouse::getPosition(*this->window);
}

void Game::mouseLeftRightPressed(){
    if (sfEvent.type == sf::Event::MouseButtonPressed) {
        if (sfEvent.mouseButton.button == sf::Mouse::Left) {
            mouseInput.setLeftClick(true);
        } else if (sfEvent.mouseButton.button == sf::Mouse::Right) {
            mouseInput.setRightClick(true);
        }
    }
}

void Game::mouseLeftRightReleased(){
    if (sfEvent.type == sf::Event::MouseButtonReleased) {
        if (sfEvent.mouseButton.button == sf::Mouse::Left) {
            if (mouseInput.isLeftClick()){

                if (gameState==GAMEMENU){

                    changeStateToStart();
                }else if(gameState==GAMESTART){


                    minesweeperBoard.revealFiled(mouseInput.mousePos.y / tileSize, mouseInput.mousePos.x / tileSize);

                    minesweeperBoard.setMines();
                    changeStateToContinue();

                }else if(gameState==GAMECONTINUE){

                    minesweeperBoard.revealFiled(mouseInput.mousePos.y / tileSize, mouseInput.mousePos.x / tileSize);

                }else if(gameState==GAMELOST){

                    changeStateToMenu();
                    windowSwitchWindowToMenu();

                }else if(gameState==GAMEWIN){

                    changeStateToMenu();
                    windowSwitchWindowToMenu();

                }

                mouseInput.setLeftClick(false);
            }

        } else if (sfEvent.mouseButton.button == sf::Mouse::Right) {
            if (mouseInput.isRightClick()){

                if (gameState==GAMEMENU){

                }else if(gameState==GAMESTART){

                    // MYSLE, ZE PRZED ULOZENIEM MIN, NIE POWINNISMY MIEC
                    // MOZLIWOSCI USTAWIENIA FLAGI

                    // minesweeperBoard.toggleFlag(mouseInput.mousePos.y / tileSize, mouseInput.mousePos.x / tileSize);

                }else if(gameState==GAMECONTINUE){

                    minesweeperBoard.toggleFlag(mouseInput.mousePos.y / tileSize, mouseInput.mousePos.x / tileSize);

                }else if(gameState==GAMELOST){

                }else if(gameState==GAMEWIN){

                }

                mouseInput.setRightClick(false);
            }
        }
    }
}

void Game::gameLoop() {


    while (this->window->isOpen()){

        this->windowClose();

        this->update();
        this->render();

    }

}

void Game::mouseUpdate(){
    this->trackMouse();
    this->mouseLeftRightPressed();
    this->mouseLeftRightReleased();
}

void Game::windowClose() {
        while (this->window->pollEvent(this->sfEvent)){
        if (sfEvent.type==sf::Event::Closed){
            this->window->close();
        }
    }
}

void Game::windowSwitchWindowToGame() {
    delete this->window;

    this->windowBounds.width= minesweeperBoard.boardWidth * 48;
    this->windowBounds.height= minesweeperBoard.boardHeight * 48;

    this->window=new sf::RenderWindow((this->windowBounds), this->windowName);
}

void Game::windowSwitchWindowToMenu() {
    delete this->window;

    this->windowBounds.width = this->windowWidth;
    this->windowBounds.height = this->windowHeight;

    this->window=new sf::RenderWindow((this->windowBounds), this->windowName);
}

void Game::update() {
    mouseUpdate();
    updateGameStatus();
}

void Game::render(){
    this->window->clear();

    if (gameState==GAMEMENU){
        menuGameRender();
    }else if (gameState==GAMESTART){
        inGameRender();
    }else if (gameState==GAMECONTINUE){
        inGameRender();
    }else if (gameState==GAMEWIN){
        winGameRender();
    }else if (gameState==GAMELOST){
        loseGameRender();
    }

    this->window->display();
}

void Game::inGameRender() {
    int scale=4;
    int x=0;
    int y=0;

    for (int i = 0; i < minesweeperBoard.boardHeight; i++) {
        for (int j = 0; j < minesweeperBoard.boardWidth; j++) {

            this->sprite.setTexture(textures[setTextures(i,j)]);
            this->sprite.setScale(scale,scale);
            sprite.setPosition(y * scale, x * scale);

            this->window->draw(sprite);
            y+=12;
        }
        y=0;
        x+=12;
    }

}

void Game::menuGameRender() {

}

void Game::winGameRender() {

}

void Game::loseGameRender() {

}

void Game::updateGameStatus() {

    if (gameState==GAMECONTINUE){
        win();
        lose();
    }

}

bool Game::isLost(){
    bool isLost = false;

    for (int forHeight = 0; forHeight < minesweeperBoard.boardHeight; ++forHeight) {
        for (int forWidth = 0; forWidth < minesweeperBoard.boardWidth; ++forWidth) {
            if (minesweeperBoard.boardVector[forHeight][forWidth].isRevealed){
                if (minesweeperBoard.boardVector[forHeight][forWidth].hasMine){
                    isLost = true;
                }
            }
        }
    }

    return isLost;
}

void Game::clearBoard() {

    for (int forHeight = 0; forHeight < minesweeperBoard.boardHeight; ++forHeight) {
        for (int forWidth = 0; forWidth < minesweeperBoard.boardWidth; ++forWidth) {
            minesweeperBoard.boardVector[forHeight][forWidth].hasMine = false;
            minesweeperBoard.boardVector[forHeight][forWidth].isRevealed = false;
            minesweeperBoard.boardVector[forHeight][forWidth].hasFlag = false;

        }
    }

}

void Game::lose() {

    if (isLost()){
        changeStateToLose();
        clearBoard();
    }

}

void Game::win() {

    if (minesweeperBoard.minesOnBoardCounterForDev() == 0){
        changeStateToWin();
        clearBoard();
    }

}
