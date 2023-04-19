#ifndef MINESWEEPER_FF_GAME_H
#define MINESWEEPER_FF_GAME_H

#include "minesweeperBoard.h"

class Game {
private:
    sf::RenderWindow *window;
    sf::VideoMode windowBounds;

    sf::Event sfEvent;

    sf::Texture texture;
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;

    int windowHeight;
    int windowWidth;

    std::string windowName;

    bool rightClick;
    bool leftClick;

public:

    Game();
    void inGameRender();
    void gameLoop();


    int setTextures(minesweeperBoard *minesweeperBoard, int height, int width);

    // WINDOW //
    void windowClose();
    void windowSwitchWindowToGame();

    // INIT //
    void initWindow();
    void initVariables();
    void initTextures();

    void initGame();

    void render();
};


#endif
