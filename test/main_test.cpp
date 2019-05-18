//
// Created by Dmitry Kulshin on 2019-05-18.
//
#include <gtest/gtest.h>
#include "../src/Board.h"
#include "../src/Cell.h"
#include "../src/IO.h"

TEST (Board, changeNumb) {
    Board board;
EXPECT_EQ (board.changeNumb('1'), 1);
EXPECT_EQ (board.changeNumb('a'), 1);
}