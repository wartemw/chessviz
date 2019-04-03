//
// Created by wartemw on 02.04.19.
//

#ifndef CHESSVIZ_IO_H
#define CHESSVIZ_IO_H

#include "Board.h"
#include <fstream>
#include <regex>
#include <sstream>
#include <vector>

class IO {
public:
    static void writeBoard(Board board);

    static vector<std::string> split(const string& s, char delimiter);

    static void
    readCommands(Board board, vector<MoveChessman>* movesChessman, istream* is);

private:
    static bool isRegular(const string& line, const regex& regex);

    static MoveChessman getMoveChessman(string line);
};

#endif // CHESSVIZ_IO_H
