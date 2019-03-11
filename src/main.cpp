//
// Created by wartemw on 06.03.19.
//
#include <iostream>

using namespace std;

enum Color {
    BLACK, WHITE
};

enum Chessman {
    KING, QUEEN, ROOK, K_NIGHT, BISHOP, PAWN, NON
};

class Cell {
private:
    Chessman chessman;
    Color colorChessman;
public:
    Cell() : chessman(NON), colorChessman(BLACK) {}

    Cell(Chessman chessman) : chessman(chessman), colorChessman(BLACK) {}

    Cell(Chessman chessman, Color colorChessman) : chessman(chessman), colorChessman(colorChessman) {}

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

int main() {
    return 0;
}