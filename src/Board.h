//
// Created by wartemw on 02.04.19.
//

#ifndef CHESSVIZ_BOARD_H
#define CHESSVIZ_BOARD_H

#include "Cell.h"
#include <ostream>
#include <string>

using namespace std;

struct MoveChessman {
    string move;
    char firstFigure = ' ';
    char firstRow = ' ';
    char firstCol = ' ';
    char type = ' ';
    char endFigure = ' ';
    char endRow = ' ';
    char endCol = ' ';
    bool shah;
    bool mat;
    bool castling;
};

class Board {
private:
    static const int NUMBER_OF_CELLS = 8;
    Cell cells[NUMBER_OF_CELLS][NUMBER_OF_CELLS];

public:
    Board();

    friend ostream& operator<<(ostream& os, const Board& board);

    void setDefault();

    int changeNumb(char letter);

    void moveChessman(MoveChessman& chessman);
};

#endif // CHESSVIZ_BOARD_H
