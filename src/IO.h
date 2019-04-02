//
// Created by wartemw on 02.04.19.
//

#ifndef CHESSVIZ_IO_H
#define CHESSVIZ_IO_H

#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include "Board.h"

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


#endif //CHESSVIZ_IO_H
