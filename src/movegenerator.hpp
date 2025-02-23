#ifndef MOVEGENERATOR_HPP
#define MOVEGENERATOR_HPP

#include <vector>
#include "chessengine.hpp"

class Move;
class ChessEngine;

/**
 * @class MoveGenerator
 * @brief Generates possible moves for chess pieces on the board.
 */
class MoveGenerator {
public:
    /**
     * @brief Generates all possible moves for the specified player.
     * @param engine The chess engine containing the game state.
     * @param player The player for whom moves are to be generated (0 for white, 1 for black).
     * @return A vector of all possible moves for the player.
     */
    static std::vector<Move> generateAllMoves(const ChessEngine& engine, int player);

    /**
     * @brief Generates all valid moves for the specified player, excluding moves that leave the king in check.
     * @param engine The chess engine containing the game state.
     * @param player The player for whom valid moves are to be generated (0 for white, 1 for black).
     * @return A vector of all valid moves for the player.
     */
    static std::vector<Move> generateAllValidMoves(const ChessEngine& engine, int player);

    /**
     * @brief Generates all possible pawn moves for the specified player.
     * @param engine The chess engine containing the game state.
     * @param player The player for whom pawn moves are to be generated (0 for white, 1 for black).
     * @return A vector of all possible pawn moves for the player.
     */
    static std::vector<Move> generatePawnMoves(const ChessEngine& engine, int player);

    /**
     * @brief Generates all possible knight moves for the specified player.
     * @param engine The chess engine containing the game state.
     * @param player The player for whom knight moves are to be generated (0 for white, 1 for black).
     * @return A vector of all possible knight moves for the player.
     */
    static std::vector<Move> generateKnightMoves(const ChessEngine& engine, int player);

    /**
     * @brief Generates all possible bishop moves for the specified player.
     * @param engine The chess engine containing the game state.
     * @param player The player for whom bishop moves are to be generated (0 for white, 1 for black).
     * @return A vector of all possible bishop moves for the player.
     */
    static std::vector<Move> generateBishopMoves(const ChessEngine& engine, int player);

    /**
     * @brief Generates all possible rook moves for the specified player.
     * @param engine The chess engine containing the game state.
     * @param player The player for whom rook moves are to be generated (0 for white, 1 for black).
     * @return A vector of all possible rook moves for the player.
     */
    static std::vector<Move> generateRookMoves(const ChessEngine& engine, int player);

    /**
     * @brief Generates all possible queen moves for the specified player.
     * @param engine The chess engine containing the game state.
     * @param player The player for whom queen moves are to be generated (0 for white, 1 for black).
     * @return A vector of all possible queen moves for the player.
     */
    static std::vector<Move> generateQueenMoves(const ChessEngine& engine, int player);

    /**
     * @brief Generates all possible king moves for the specified player.
     * @param engine The chess engine containing the game state.
     * @param player The player for whom king moves are to be generated (0 for white, 1 for black).
     * @return A vector of all possible king moves for the player.
     */
    static std::vector<Move> generateKingMoves(const ChessEngine& engine, int player);

    /**
     * @brief Converts a position index to UCI format.
     * @param position The position index (0-63).
     * @return A string representing the position in UCI format.
     */
    static std::string positionToUCI(int position);
};

#endif // MOVEGENERATOR_HPP