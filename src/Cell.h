//
// Created by wartemw on 02.04.19.
//

#ifndef CHESSVIZ_CELL_H
#define CHESSVIZ_CELL_H

#include <ostream>

using namespace std;

enum Color { BLACK, WHITE };

enum Chessman { KING, QUEEN, ROOK, K_NIGHT, BISHOP, PAWN, NON };

class Cell {
private:
    Chessman chessman;
    Color colorChessman;

public:
    Cell();

    Cell(Chessman chessman);

    Cell(Chessman chessman, Color colorChessman);

    char designation() const;

    friend ostream& operator<<(ostream& os, const Cell& cell);
};

#endif // CHESSVIZ_CELL_H
