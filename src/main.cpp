//
// Created by wartemw on 06.03.19.
//
#include <iostream>
#include <fstream>
#include <list>
#include <regex>

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

    friend ostream &operator<<(ostream &os, const Board &board) {
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

class IO {
public:
    static void writeBoard(Board board) {
        ofstream oFile;
        oFile.open("../res/output.txt");
        oFile << board;
        oFile.close();
    }

    static vector<std::string> split(const string &s, char delimiter) {
        vector<std::string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static void readCommands(Board board, vector<MoveChessman> *movesChessman, istream *is) {
        string line;

        while (getline(*is, line)/*|| strcmp(line.c_str(), "exit")*/) {
            vector<string> lineSplit = split(line, ' ');

            for (int i = 1; i < lineSplit.size(); ++i) {
                movesChessman->push_back(getMoveChessman(lineSplit[i]));
            }
        }
    }

private:

    static bool isRegular(const string line, const regex regex) {
        return regex_search(line.c_str(), regex);
    }

    static MoveChessman getMoveChessman(string line) {
        MoveChessman moveChessman{};
        moveChessman.move = line;

        regex castling("([0-9]. )?(0-0-0|0-0)");
        regex pawnMove("([a-z])([0-9])(-|x)([a-z])([0-9])");
        regex firstFigureMove("([A-Z])([a-z])([0-9])(-|x)([a-z])([0-9])");
        regex endFigureMove("([a-z])([0-9])(-|x)([A-Z])([a-z])([0-9])");
        regex allFigureMove("([A-Z])([a-z])([0-9])(-|x)([A-Z])([a-z])([0-9])");

        if (isRegular(line, castling)) {
            moveChessman.castling = true;

        } else if (isRegular(line, allFigureMove)) {
            moveChessman.firstFigure = line[0];
            moveChessman.firstRow = line[1];
            moveChessman.firstCol = line[2];
            moveChessman.type = line[3];
            moveChessman.endFigure = line[4];
            moveChessman.endRow = line[5];
            moveChessman.endCol = line[6];
            if (line.length() == 8) {
                if (line[7] == '#') moveChessman.mat = true;
                if (line[7] == '+') moveChessman.shah = true;
            }

        } else if (isRegular(line, firstFigureMove)) {

            moveChessman.firstFigure = line[0];
            moveChessman.firstRow = line[1];
            moveChessman.firstCol = line[2];
            moveChessman.type = line[3];
            moveChessman.endRow = line[4];
            moveChessman.endCol = line[5];
            if (line.length() == 7) {
                if (line[6] == '#') moveChessman.mat = true;
                if (line[6] == '+') moveChessman.shah = true;
            }

        } else if (isRegular(line, endFigureMove)) {

            moveChessman.firstRow = line[0];
            moveChessman.firstCol = line[1];
            moveChessman.type = line[2];
            moveChessman.firstFigure = line[3];
            moveChessman.endRow = line[4];
            moveChessman.endCol = line[5];
            if (line.length() == 7) {
                if (line[6] == '#') moveChessman.mat = true;
                if (line[6] == '+') moveChessman.shah = true;
            }

        } else if (isRegular(line, pawnMove)) {
            moveChessman.firstRow = line[0];
            moveChessman.firstCol = line[1];
            moveChessman.type = line[2];
            moveChessman.endRow = line[3];
            moveChessman.endCol = line[4];
            if (line.length() == 6) {
                if (line[5] == '#') moveChessman.mat = true;
                if (line[5] == '+') moveChessman.shah = true;
            }
        }
        return moveChessman;
    }
};

int main(int argc, char *argv[]) {
    Board board;
    ifstream input;
    input.open(argv[1]);
    vector<MoveChessman> movesChessman;

    IO::readCommands(board, &movesChessman, &input);

    for (MoveChessman &moveChessman : movesChessman) {
        board.moveChessman(moveChessman);
        cout << moveChessman.move << endl << endl;
        cout << board << endl << endl;
    }

    IO::writeBoard(board);
    return 0;
}