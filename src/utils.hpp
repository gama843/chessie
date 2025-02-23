#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>
#include <string>
#include "chessengine.hpp"

/**
 * @class Utils
 * @brief Utility functions for the chess engine.
 */
class Utils {
public:
    /**
     * @brief Prints the current state of the chessboard.
     * @param engine The chess engine containing the game state.
     */
    static void printBoard(const ChessEngine& engine);

    /**
     * @brief Prints a bitboard.
     * @param bitboard The bitboard to print.
     */
    static void printBitboard(uint64_t bitboard);

    /**
     * @brief Evaluates the current board state from the perspective of a player.
     * @param engine The chess engine containing the game state.
     * @param player The player to evaluate the board for (0 for white, 1 for black).
     * @return The evaluation score.
     */
    static int evaluateBoard(const ChessEngine& engine, int player);

    /**
     * @brief Gets the current game status.
     * @param engine The chess engine containing the game state.
     * @param player The player to get the game status for (0 for white, 1 for black).
     * @return The game status as a string.
     */
    static std::string getGameStatus(const ChessEngine& engine, int player);

    /**
     * @brief Prints the help message.
     */
    static void printHelp();

    /**
     * @brief Converts a position to UCI notation.
     * @param position The position to convert.
     * @return The position in UCI notation.
     */
    static std::string positionToUCI(int position);

    /**
     * @brief Prints a list of moves.
     * @param moves The list of moves to print.
     */
    static void printMoves(const std::vector<Move>& moves);

    /**
     * @brief Checks if the current game state is a draw due to insufficient material.
     * @param engine The chess engine containing the game state.
     * @return True if the game is a draw due to insufficient material, false otherwise.
     */
    static bool isInsufficientMaterial(const ChessEngine& engine);
};

#endif // UTILS_HPP