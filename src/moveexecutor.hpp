#ifndef MOVEEXECUTOR_HPP
#define MOVEEXECUTOR_HPP

#include "chessengine.hpp"

/**
 * @class MoveExecutor
 * @brief Executes moves on the chessboard for a given player.
 */
class MoveExecutor {
public:
    /**
     * @brief Executes a move on the chessboard for the specified player.
     * @param engine The chess engine containing the game state.
     * @param move The move to be executed.
     * @param player The player making the move (0 for white, 1 for black).
     */
    static void makeMove(ChessEngine& engine, const Move& move, int player);

private:
    /**
     * @brief Removes a piece from the specified bitboard at the given square.
     * @param bitboard The bitboard from which the piece is to be removed.
     * @param square The square index (0-63) from which the piece is to be removed.
     */
    static void removePiece(uint64_t& bitboard, int square);

    /**
     * @brief Places a piece on the specified bitboard at the given square.
     * @param bitboard The bitboard on which the piece is to be placed.
     * @param square The square index (0-63) on which the piece is to be placed.
     */
    static void placePiece(uint64_t& bitboard, int square);
};

#endif // MOVEEXECUTOR_HPP