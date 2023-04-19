#ifndef MINESWEEPER_FF_MINESWEEPERBOARD_H
#define MINESWEEPER_FF_MINESWEEPERBOARD_H

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include <iostream>
#include <vector>

struct Field{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;

};

class minesweeperBoard {
private:

public:

    std::vector<std::vector<Field>> boardVector;

    int boardHeight;
    int boardWidth;

    minesweeperBoard();

    void genBoard();
    void clearBoard();
    void setMines();


    // INIT //
    void initVariables();

    // FIELD CONSTRUCTOR //
    void fieldStructConstructor(Field *field, bool hasMine, bool hasFlag, bool isRevealed);

    // DEBUG //
    void debugDisplay() const;

    // FUNCTIONS //
    void toggleFlag(int height, int width);
    void revealFiled(int height, int width);

    int minesAroundField(int height, int width);

    int minesAroundFieldFun(int forHeight, int forWidth, int height, int width);
};


#endif