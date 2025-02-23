#include <gtest/gtest.h>
#include "chessengine.hpp"
#include "movevalidator.hpp"

// test move validation for various scenarios
TEST(MoveValidatorTest, ValidMoves) {
    ChessEngine engine;
    engine.newGame();

    // test valid pawn move
    Move move("e2e4");
    EXPECT_TRUE(MoveValidator::isValidMove(move, 0, engine));

    // test valid knight move
    move = Move("g1f3");
    EXPECT_TRUE(MoveValidator::isValidMove(move, 0, engine));
}

TEST(MoveValidatorTest, InvalidMoves) {
    ChessEngine engine;
    engine.newGame();

    // test invalid pawn move
    Move move("e2e5");
    EXPECT_FALSE(MoveValidator::isValidMove(move, 0, engine));

    // test invalid knight move
    move = Move("g1g3");
    EXPECT_FALSE(MoveValidator::isValidMove(move, 0, engine));
}