//
// Created by wartemw on 02.04.19.
//

#ifndef CHESSVIZ_CELL_H
#define CHESSVIZ_CELL_H

#include "Board.h"


class Cell {
private:
    Chessman chessman;
    Color colorChessman;
public:
    Cell() : chessman(NON), colorChessman(BLACK) {}

    Cell(Chessman chessman) : chessman(chessman), colorChessman(BLACK) {}

    Cell(Chessman chessman, Color colorChessman) : chessman(chessman), colorChessman(colorChessman) {}

    friend ostream &operator<<(ostream &os, const Cell &cell) {
        os << cell.designation();
        return os;
    }


    char designation() const {
        switch (chessman) {
            case KING:
                return colorChessman == WHITE ? 'K' : 'k';
            case QUEEN:
                return colorChessman == WHITE ? 'Q' : 'q';
            case ROOK:
                return colorChessman == WHITE ? 'R' : 'r';
            case K_NIGHT:
                return colorChessman == WHITE ? 'N' : 'n';
            case BISHOP:
                return colorChessman == WHITE ? 'B' : 'b';
            case PAWN:
                return colorChessman == WHITE ? 'P' : 'p';
            default:
                return '_';
        }
    }
};


#endif //CHESSVIZ_CELL_H
