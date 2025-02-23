#include <gtest/gtest.h>
#include "chessengine.hpp"
#include "utils.hpp"

// functional test for an incomplete game
TEST(FunctionalTest, GameInProgress) {
    ChessEngine engine;
    engine.newGame();

    // simulate a series of moves
    std::vector<std::string> moves = {"e2e4", "e7e5", "g1f3", "b8c6", "f1b5", "a7a6", "b5a4", "g8f6"};
    int player = 0;
    for (const auto& move : moves) {
        engine.makeMove(Move(move), player);
        player = 1 - player;
    }

    // check game status after moves
    GameStatus status = engine.getGameStatus();
    EXPECT_EQ(status, GameStatus::IN_PROGRESS);
}

// functional test for a complete game
TEST(FunctionalTest, CheckMate) {
    ChessEngine engine;
    engine.newGame();

    // simulate a series of moves for the fastest checkmate possible
    std::vector<std::string> moves = {"e2e4", "a7a6", "f1c4", "a6a5", "d1h5", "a5a4", "h5f7"};
    int player = 0;
    for (const auto& move : moves) {
        engine.makeMove(Move(move), player);
        player = 1 - player;
    }

    // check game status after moves
    GameStatus status = engine.getGameStatus();
    EXPECT_EQ(status, GameStatus::BLACK_CHECKMATED);
}