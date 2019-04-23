//
// Created by wartemw on 06.03.19.
//
#include "Board.h"
#include "Cell.h"
#include "IO.h"
#include <fstream>
#include <iostream>
#include <list>
#include <regex>

int main(int argc, char* argv[])
{
    Board board;
    ifstream input;
    input.open(argv[1]);
    vector<MoveChessman> movesChessman;

    IO::readCommands(board, &movesChessman, &input);

    for (MoveChessman& moveChessman : movesChessman) {
        board.moveChessman(moveChessman);
        cout << moveChessman.move << endl << endl;
        cout << board << endl << endl;
    }

    IO::writeBoard(board);
    return 0;
}