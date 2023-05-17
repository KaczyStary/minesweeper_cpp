#ifndef MINESWEEPER_FF_GAME_H
#define MINESWEEPER_FF_GAME_H

#include "MinesweeperBoard.h"
#include "MouseInput.h"
#include "Button.h"

enum GameState{
    GAMEMENU,
    GAMESTART,
    GAMECONTINUE,
    GAMEWIN,
    GAMELOST
};

class Game {
private:
    sf::RenderWindow *window;
    sf::VideoMode windowBounds;
    std::string windowName;

    sf::Event sfEvent;

    sf::Texture texture;
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;

    int windowHeight;
    int windowWidth;

    MinesweeperBoard minesweeperBoard;
    MouseInput mouseInput;

    GameState gameState;

    int tileSize=48; // 48 pix

public:

    Game();
    void gameLoop();

    // RENDER //

    void render();
    void inGameRender();
    void menuGameRender();
    void winGameRender();
    void loseGameRender();


    // WINDOW //
    void windowClose();
    void windowSwitchWindowToGame();
    void windowSwitchWindowToMenu();


    // INIT //
    void initWindow();
    void initVariables();
    void initTextures();
    int setTextures(int height, int width);

    // MOUSE //
    void mouseLeftRightPressed();
    void mouseLeftRightReleased();
    void trackMouse();

    // STATES //
    void initState();
    void changeStateToStart();
    void changeStateToMenu();
    void changeStateToContinue();
    void changeStateToWin();
    void changeStateToLose();

    // UPDATE //
    void update();
    void mouseUpdate();
    void updateGameStatus();

    // WIN/LOSE FUNCTIONS/INSTRUCTIONS //
    bool isLost();
    void clearBoard();

    void lose();
    void win();

};


#endif
