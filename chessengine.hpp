#ifndef CHESSENGINE_HPP
#define CHESSENGINE_HPP

#include <cstdint>
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
    void printBoard();
    void printBitboard(uint64_t bitboard);

    // castling
    bool canCastleKingside(int player);
    bool canCastleQueenside(int player);

    // make bitboards public for testing and debugging
    uint64_t whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens, whiteKing;
    uint64_t blackPawns, blackKnights, blackBishops, blackRooks, blackQueens, blackKing;

    // getter and setter methods for castling flags
    bool getWhiteKingMoved() const;
    void setWhiteKingMoved(bool moved);
    bool getWhiteRookA1Moved() const;
    void setWhiteRookA1Moved(bool moved);
    bool getWhiteRookH1Moved() const;
    void setWhiteRookH1Moved(bool moved);
    bool getBlackKingMoved() const;
    void setBlackKingMoved(bool moved);
    bool getBlackRookA8Moved() const;
    void setBlackRookA8Moved(bool moved);
    bool getBlackRookH8Moved() const;
    void setBlackRookH8Moved(bool moved);

private:
    bool isWithinBoard(int square);
    void removePiece(uint64_t& bitboard, int square);
    void placePiece(uint64_t& bitboard, int square);
    
    // castling flags
    bool whiteKingMoved, whiteRookA1Moved, whiteRookH1Moved;
    bool blackKingMoved, blackRookA8Moved, blackRookH8Moved;
};

#endif // CHESSENGINE_HPP
