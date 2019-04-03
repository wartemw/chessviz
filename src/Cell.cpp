//
// Created by wartemw on 02.04.19.
//

#include "Cell.h"

Cell::Cell() : chessman(NON), colorChessman(BLACK)
{
}

Cell::Cell(Chessman chessman) : chessman(chessman), colorChessman(BLACK)
{
}

Cell::Cell(Chessman chessman, Color colorChessman)
    : chessman(chessman), colorChessman(colorChessman)
{
}

ostream& operator<<(ostream& os, const Cell& cell)
{
    os << cell.designation();
    return os;
}

char Cell::designation() const
{
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
