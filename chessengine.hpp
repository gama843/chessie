#ifndef CHESSENGINE_HPP
#define CHESSENGINE_HPP

#include <cstdint> // For uint64_t
#include <string>
#include <vector>
#include "movegenerator.hpp"

struct Move {
    int from;
    int to;
    Move(int f, int t) : from(f), to(t) {}
};

class ChessEngine {
public:
    ChessEngine();
    void newGame();
    void loadGameFromFile(const std::string& path);
    void saveGameToFile(const std::string& path);
    std::string getGameStatus();
    bool isValidMove(const Move& move, int player);
    void makeMove(const Move& move, int player);
    int getCurrentValue(int player);
    Move makeNaiveMove(int player);
    void printBoard(); // Add this line
    void printBitboard(uint64_t bitboard); // Add this line

    // Make bitboards public for testing and debugging
    uint64_t whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens, whiteKing;
    uint64_t blackPawns, blackKnights, blackBishops, blackRooks, blackQueens, blackKing;

private:
    bool isWithinBoard(int square);
    void removePiece(uint64_t& bitboard, int square);
    void placePiece(uint64_t& bitboard, int square);
};

#endif // CHESSENGINE_HPP