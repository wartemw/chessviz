//
// Created by wartemw on 02.04.19.
//

#ifndef CHESSVIZ_BOARD_H
#define CHESSVIZ_BOARD_H

#include "Cell.h"
#include <string>
using namespace std;

enum Color { BLACK, WHITE };

enum Chessman { KING, QUEEN, ROOK, K_NIGHT, BISHOP, PAWN, NON };

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
    Board()
    {
        setDefault();
    }

    friend ostream& operator<<(ostream& os, const Board& board)
    {
        for (int i = NUMBER_OF_CELLS - 1; i >= 0; --i) {
            os << i + 1 << ' ';
            for (int j = 0; j < NUMBER_OF_CELLS; ++j) {
                os << board.cells[i][j] << ' ';
            }
            os << '\n';
        }
        os << "  ";
        for (char i = 'a'; i <= 'h'; ++i)
            os << i << ' ';
        return os;
    }

    void setDefault()
    {
        cells[0][0] = Cell(ROOK, WHITE);
        cells[0][1] = Cell(K_NIGHT, WHITE);
        cells[0][2] = Cell(BISHOP, WHITE);
        cells[0][3] = Cell(QUEEN, WHITE);
        cells[0][4] = Cell(KING, WHITE);
        cells[0][5] = Cell(BISHOP, WHITE);
        cells[0][6] = Cell(K_NIGHT, WHITE);
        cells[0][7] = Cell(ROOK, WHITE);
        for (int i = 0; i < NUMBER_OF_CELLS; ++i)
            cells[1][i] = Cell(PAWN, WHITE);

        cells[7][0] = Cell(ROOK);
        cells[7][1] = Cell(K_NIGHT);
        cells[7][2] = Cell(BISHOP);
        cells[7][3] = Cell(QUEEN);
        cells[7][4] = Cell(KING);
        cells[7][5] = Cell(BISHOP);
        cells[7][6] = Cell(K_NIGHT);
        cells[7][7] = Cell(ROOK);
        for (int i = 0; i < NUMBER_OF_CELLS; ++i)
            cells[6][i] = Cell(PAWN);
    }

    int changeNumb(char letter)
    {
        if ('0' < letter && letter < '9')
            return letter - '0' - 1;
        if ('a' < letter && letter < 'z')
            return letter - 'a';
        return letter;
    }

    void moveChessman(MoveChessman& chessman)
    {
        // cout << endl << changeNumb(chessman.firstRow) << " | " <<
        // changeNumb(chessman.firstCol) << endl; cout <<
        // changeNumb(chessman.endRow) << " | " << changeNumb(chessman.endCol)
        // << endl << endl;
        if (chessman.type == '-') {
            Cell temp = cells[changeNumb(chessman.firstCol)]
                             [changeNumb(chessman.firstRow)];
            cells[changeNumb(chessman.firstCol)][changeNumb(chessman.firstRow)]
                    = cells[changeNumb(chessman.endCol)]
                           [changeNumb(chessman.endRow)];
            cells[changeNumb(chessman.endCol)][changeNumb(chessman.endRow)]
                    = temp;
        } else {
            cells[changeNumb(chessman.endCol)][changeNumb(chessman.endRow)]
                    = cells[changeNumb(chessman.firstCol)]
                           [changeNumb(chessman.firstRow)];
            Cell cell;
            cells[changeNumb(chessman.firstCol)][changeNumb(chessman.firstRow)]
                    = cell;
        }
    }
};

#endif // CHESSVIZ_BOARD_H
