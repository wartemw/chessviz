//
// Created by wartemw on 06.03.19.
//

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

};

int main() {
    return 0;
}