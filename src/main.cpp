#include <iostream>
#include "chessengine.hpp"
#include "utils.hpp"

/**
 * \mainpage
 *
 * \section intro Introduction
 *
 * This is the documentation for Chessie - a prototype chess engine providing fast and efficient representation and manipulation of chess game states. The engine is designed to support various game modes, including human vs human, human vs AI, and AI vs AI. It also includes features such as move validation, move generation, and board evaluation.
 *
 * \section features Features
 * - Supports human vs human, human vs AI, and AI vs AI game modes.
 * - Provides move validation and move generation.
 * - Includes board evaluation using a simple material-based evaluation function.
 * - Supports command-line arguments to set up the game mode.
 * - Provides a simple ASCII-based user interface for human players.
 * - Includes a simple AI player using a random or greedy move strategy.
 * - Uses UCI (Universal Chess Interface) for move notation.
 */

/**
 * @brief Main function for the chess engine program.
 *
 * This function initializes the ChessEngine, parses command-line arguments to set up the game mode,
 * and starts the game.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char* argv[]) {
    ChessEngine engine; /**< The chess engine instance. */
    engine.parseArgs(argc, argv); /**< Parses the args and acts correspondingly. */
    return 0;
}