#include "MinesweeperBoard.h"

void MinesweeperBoard::initVariables() {
    this->boardWidth=10;
    this->boardHeight=10;

}

MinesweeperBoard::MinesweeperBoard() {
    initVariables();
    genBoard();
}

void MinesweeperBoard::debugDisplay() const {

    for (const auto &i: boardVector) {
        for (auto j: i) {

            std::cout << "[";
            std::cout << j.hasMine;
            if (j.hasFlag) {
                std::cout << "F";
            } else {
                std::cout << j.hasFlag;
            }
            if (j.isRevealed) {
                std::cout << "R";
            } else {
                std::cout << j.isRevealed;
            }
            std::cout << "] ";

        }
        std::cout << std::endl;
    }

}

void MinesweeperBoard::genBoard() {
    for (int i = 0; i < this->boardHeight; i++) {
        std::vector<Field> row;
        for (int j = 0; j < this->boardWidth; j++) {
            Field field;
            fieldStructConstructor(&field, false, false, false);
            row.push_back(field);
        }
        boardVector.push_back(row);
    }
}

void MinesweeperBoard::fieldStructConstructor(struct Field *field, bool hasMine, bool hasFlag, bool isRevealed) {
    field->hasMine=hasMine;
    field->hasFlag=hasFlag;
    field->isRevealed=isRevealed;
}

void MinesweeperBoard::setMines() {

    srand(time(nullptr));

    double numberOfMinesForEasy=0.1;
    int minRandomHeightWidth=0;
    int maxRandomWidth=boardWidth;
    int maxRandomHeight=boardHeight;

    int numberOfMines=0;
    numberOfMines=boardHeight*boardWidth*numberOfMinesForEasy;

        while (numberOfMines>0){

            int randomHeight=rand() % (maxRandomHeight - minRandomHeightWidth) + minRandomHeightWidth;
            int randomWidth=rand() % (maxRandomWidth - minRandomHeightWidth) + minRandomHeightWidth;

            if (!boardVector[randomHeight][randomWidth].hasMine&&!boardVector[randomHeight][randomWidth].isRevealed) {
                boardVector[randomHeight][randomWidth].hasMine = true;
                numberOfMines--;
            }
        }

}

int MinesweeperBoard::minesAroundFieldFun(int forHeight, int forWidth, int height, int width){
    int minesAroundField = 0;

    if (boardVector[forHeight][forWidth].hasMine) {
        minesAroundField++;
    }

    if (height == forHeight && width == forWidth) {
        if (boardVector[forHeight][forWidth].hasMine) {
            minesAroundField--;
        }
    }

    return minesAroundField;
}

int MinesweeperBoard::minesAroundField(int height, int width) {
    int minesAroundField = 0;

    //UPPER LIMIT
    if ( height == 0 && width !=0 && width != (boardWidth-1) ) {
        for (int forHeight = height; forHeight <= height + 1; ++forHeight ) {
            for (int forWidth = width - 1; forWidth <= width + 1; ++forWidth ) {

                if (boardVector[forHeight][forWidth].hasMine) {
                    minesAroundField++;
                }

                if (height == forHeight && width == forWidth) {
                    if (boardVector[forHeight][forWidth].hasMine) {
                        minesAroundField--;
                    }
                }

            }
        }
        //LOWER LIMIT
    }else if (height==boardHeight-1&&width!=0&&width!=(boardWidth-1)) {
        for (int forHeight = height - 1; forHeight <= height; ++forHeight) {
            for (int forWidth = width - 1; forWidth <= width + 1; ++forWidth) {

                if (boardVector[forHeight][forWidth].hasMine) {
                    minesAroundField++;
                }

                if (height == forHeight && width == forWidth) {
                    if (boardVector[forHeight][forWidth].hasMine) {
                        minesAroundField--;
                    }
                }

            }
        }
        //LEFT LIMIT
    }else if (width==0&&height!=0&&height!=boardHeight-1) {

        for (int forHeight = height - 1; forHeight <= height + 1; ++forHeight) {
            for (int forWidth = width; forWidth <= width + 1; ++forWidth) {

                if (boardVector[forHeight][forWidth].hasMine) {
                    minesAroundField++;
                }

                if (height == forHeight && width == forWidth) {
                    if (boardVector[forHeight][forWidth].hasMine) {
                        minesAroundField--;
                    }
                }

            }
        }
        //RIGHT LIMIT
    }else if (width==boardWidth-1&&height!=0&&height!=boardHeight-1) {

        for (int forHeight = height - 1; forHeight <= height + 1; ++forHeight) {
            for (int forWidth = width - 1; forWidth <= width; ++forWidth) {

                if (boardVector[forHeight][forWidth].hasMine) {
                    minesAroundField++;
                }

                if (height == forHeight && width == forWidth) {
                    if (boardVector[forHeight][forWidth].hasMine) {
                        minesAroundField--;
                    }
                }

            }
        }
        // [0][0]
    }else if (height==0&&width==0) {

        for (int forHeight = height; forHeight <= height + 1; ++forHeight) {
            for (int forWidth = width; forWidth <= width + 1; ++forWidth) {

                if (boardVector[forHeight][forWidth].hasMine) {
                    minesAroundField++;
                }

                if (height == forHeight && width == forWidth) {
                    if (boardVector[forHeight][forWidth].hasMine) {
                        minesAroundField--;
                    }
                }

            }
        }
        // [0][LAST]
    }else if (height==0&&width==boardWidth-1) {

        for (int forHeight = height; forHeight <= height + 1; ++forHeight) {
            for (int forWidth = width - 1; forWidth <= width; ++forWidth) {

                if (boardVector[forHeight][forWidth].hasMine) {
                    minesAroundField++;
                }

                if (height == forHeight && width == forWidth) {
                    if (boardVector[forHeight][forWidth].hasMine) {
                        minesAroundField--;
                    }
                }

            }
        }
        // [LAST][LAST]
    }else if (height==boardHeight-1&&width==boardWidth-1) {

        for (int forHeight = height - 1; forHeight <= height; ++forHeight) {
            for (int forWidth = width - 1; forWidth <= width; ++forWidth) {

                if (boardVector[forHeight][forWidth].hasMine) {
                    minesAroundField++;
                }

                if (height == forHeight && width == forWidth) {
                    if (boardVector[forHeight][forWidth].hasMine) {
                        minesAroundField--;
                    }
                }

            }
        }
        //[LAST][0]
    }else if (height==boardHeight-1&&width==0) {

        for (int forHeight = height - 1; forHeight <= height; ++forHeight) {
            for (int forWidth = width; forWidth <= width + 1; ++forWidth) {

                if (boardVector[forHeight][forWidth].hasMine) {
                    minesAroundField++;
                }

                if (height == forHeight && width == forWidth) {
                    if (boardVector[forHeight][forWidth].hasMine) {
                        minesAroundField--;
                    }
                }

            }
        }
        // OTHER
    }else{

        for (int forHeight = height - 1; forHeight <= height + 1; ++forHeight) {
            for (int forWidth = width - 1; forWidth <= width + 1; ++forWidth) {

                if (boardVector[forHeight][forWidth].hasMine){
                    minesAroundField++;
                }

                if (height == forHeight && width == forWidth) {
                    if (boardVector[forHeight][forWidth].hasMine) {
                        minesAroundField--;
                    }
                }

            }
        }

    }
    return minesAroundField;
}

void MinesweeperBoard::toggleFlag(int height, int width) {

    if (!boardVector[height][width].isRevealed){

        if (!boardVector[height][width].hasFlag) {
            boardVector[height][width].hasFlag = true;

        }else if(boardVector[height][width].hasFlag){
            boardVector[height][width].hasFlag = false;
        }

    }
}

void MinesweeperBoard::revealFiled(int height, int width) {

    if (!boardVector[height][width].isRevealed){

        if (!boardVector[height][width].hasFlag) {
            boardVector[height][width].isRevealed = true;

            if (boardVector[height][width].hasMine){

            }

        }
    }
}



