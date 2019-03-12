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

class Board {

private:
    static const int NUMBER_OF_CELLS = 8;
    Cell cells[NUMBER_OF_CELLS][NUMBER_OF_CELLS];
public:
    Board() {
        setDefault();
    }

    void setDefault() {
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

    int changeNumb(char letter) {
        if ('0' < letter && letter < '9')
            return letter - '0' - 1;
        if ('a' < letter && letter < 'z')
            return letter - 'a';
        return letter;
    }

    void moveChessman(MoveChessman &chessman) {
        //cout << endl << changeNumb(chessman.firstRow) << " | " << changeNumb(chessman.firstCol) << endl;
        //cout << changeNumb(chessman.endRow) << " | " << changeNumb(chessman.endCol) << endl << endl;
        if(chessman.type == '-') {
            Cell temp = cells[changeNumb(chessman.firstCol)][changeNumb(chessman.firstRow)];
            cells[changeNumb(chessman.firstCol)][changeNumb(chessman.firstRow)] =
                    cells[changeNumb(chessman.endCol)][changeNumb(chessman.endRow)];
            cells[changeNumb(chessman.endCol)][changeNumb(chessman.endRow)] = temp;
        }else {
            cells[changeNumb(chessman.endCol)][changeNumb(chessman.endRow)] =
                    cells[changeNumb(chessman.firstCol)][changeNumb(chessman.firstRow)];
            Cell cell;
            cells[changeNumb(chessman.firstCol)][changeNumb(chessman.firstRow)] = cell;
        }
    }
};

int main() {
    return 0;
}