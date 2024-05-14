#include <iostream>
#include "chessengine.hpp"

void printHelp() {
    std::cout << "The software provides basic chess engine functionality such as recording your games, "
              << "playing for a single or both players, checking the validity of a move or evaluating a player's position. "
              << "You can run it interactively, use it to automate some chess-related workflow or even use it as a simple opponent. "
              << "You can run the program with several arguments:\n"
              << "-n --new    For a new game session.\n"
              << "-f --file   The path to the input game file. Please note that if the game is finished the program will \n"
              << "-l --log    The path to the output log file.\n"
              << "-e --eval   Returns evaluation of a player's position based on the provided ID - 0 = white, 1 = black.\n";
}

int main(int argc, char* argv[]) {
    ChessEngine engine;

    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--help" || arg == "-h") {
            printHelp();
        } else if (arg == "--new" || arg == "-n") {
            engine.newGame();
            std::cout << "New game started. Here is the initial board:" << std::endl;
            engine.printBoard();
        } else if (arg == "--file" || arg == "-f") {
            if (argc > 2) {
                engine.loadGameFromFile(argv[2]);
                std::cout << engine.getGameStatus() << std::endl;
            }
        } else if (arg == "--eval" || arg == "-e") {
            if (argc > 2) {
                int player = std::stoi(argv[2]);
                std::cout << "Evaluation for player " << player << ": " << engine.getCurrentValue(player) << std::endl;
            }
        } else {
            std::cout << "Invalid argument. Use --help or -h to see the usage instructions." << std::endl;
        }
    } else {
        std::cout << "Usage: " << argv[0] << " [--new | --file <path> | --eval <player> | --help]" << std::endl;
    }

    // Initialize new game
    engine.newGame();
    std::cout << "Initial board:" << std::endl;
    engine.printBoard();

    // Move 1: White pawn from E2 to E4
    Move move1(12, 28); // Pawn move from E2 to E4
    if (engine.isValidMove(move1, 0)) {
        std::cout << "Move 1 is valid!" << std::endl;
        engine.makeMove(move1, 0);
        std::cout << "Board after Move 1:" << std::endl;
        engine.printBoard();
        std::cout << "Evaluation for White after Move 1: " << engine.getCurrentValue(0) << std::endl;
        std::cout << "Evaluation for Black after Move 1: " << engine.getCurrentValue(1) << std::endl;
    } else {
        std::cout << "Move 1 is invalid!" << std::endl;
    }

    // Move 2: Black knight from G8 to F6
    Move move2(62, 45); // Knight move from G8 to F6
    if (engine.isValidMove(move2, 1)) {
        std::cout << "Move 2 is valid!" << std::endl;
        engine.makeMove(move2, 1);
        std::cout << "Board after Move 2:" << std::endl;
        engine.printBoard();
        std::cout << "Evaluation for White after Move 2: " << engine.getCurrentValue(0) << std::endl;
        std::cout << "Evaluation for Black after Move 2: " << engine.getCurrentValue(1) << std::endl;
    } else {
        std::cout << "Move 2 is invalid!" << std::endl;
    }

    // Move 3: White pawn from D2 to D4
    Move move3(11, 19); // Pawn move from D2 to D4
    if (engine.isValidMove(move3, 0)) {
        std::cout << "Move 3 is valid!" << std::endl;
        engine.makeMove(move3, 0);
        std::cout << "Board after Move 3:" << std::endl;
        engine.printBoard();
        std::cout << "Evaluation for White after Move 3: " << engine.getCurrentValue(0) << std::endl;
        std::cout << "Evaluation for Black after Move 3: " << engine.getCurrentValue(1) << std::endl;
    } else {
        std::cout << "Move 3 is invalid!" << std::endl;
    }

    // Move 4: Black pawn from E7 to E6
    Move move4(52, 36); // Pawn move from E7 to E6
    if (engine.isValidMove(move4, 1)) {
        std::cout << "Move 4 is valid!" << std::endl;
        engine.makeMove(move4, 1);
        std::cout << "Board after Move 4:" << std::endl;
        engine.printBoard();
        std::cout << "Evaluation for White after Move 4: " << engine.getCurrentValue(0) << std::endl;
        std::cout << "Evaluation for Black after Move 4: " << engine.getCurrentValue(1) << std::endl;
    } else {
        std::cout << "Move 4 is invalid!" << std::endl;
    }

    // Move 5: White pawn from E4 to E5
    Move move5(28, 36); // Pawn move from E4 to E5
    if (engine.isValidMove(move5, 0)) {
        std::cout << "Move 5 is valid!" << std::endl;
        engine.makeMove(move5, 0);
        std::cout << "Board after Move 5:" << std::endl;
        engine.printBoard();
        std::cout << "Evaluation for White after Move 5: " << engine.getCurrentValue(0) << std::endl;
        std::cout << "Evaluation for Black after Move 5: " << engine.getCurrentValue(1) << std::endl;
    } else {
        std::cout << "Move 5 is invalid!" << std::endl;
    }

    // Move 6: Black knight from F6 to D5
    Move move6(45, 28); // Knight move from F6 to D5
    if (engine.isValidMove(move6, 1)) {
        std::cout << "Move 6 is valid!" << std::endl;
        engine.makeMove(move6, 1);
        std::cout << "Board after Move 6:" << std::endl;
        engine.printBoard();
        std::cout << "Evaluation for White after Move 6: " << engine.getCurrentValue(0) << std::endl;
        std::cout << "Evaluation for Black after Move 6: " << engine.getCurrentValue(1) << std::endl;
    } else {
        std::cout << "Move 6 is invalid!" << std::endl;
    }

    // Move 7: White pawn from D4 to D5 (captures knight)
    Move move7(19, 28); // Pawn move from D4 to D5 (capture)
    if (engine.isValidMove(move7, 0)) {
        std::cout << "Move 7 is valid!" << std::endl;
        engine.makeMove(move7, 0);
        std::cout << "Board after Move 7:" << std::endl;
        engine.printBoard();
        std::cout << "Evaluation for White after Move 7: " << engine.getCurrentValue(0) << std::endl;
        std::cout << "Evaluation for Black after Move 7: " << engine.getCurrentValue(1) << std::endl;
    } else {
        std::cout << "Move 7 is invalid!" << std::endl;
    }

    // Save the game state to a file
    std::string filePath = "game_state.txt";
    engine.saveGameToFile(filePath);
    std::cout << "Game state saved to " << filePath << std::endl;

    // Load the game state from the file
    ChessEngine loadedEngine;
    loadedEngine.loadGameFromFile(filePath);
    std::cout << "Loaded game state from " << filePath << std::endl;
    loadedEngine.printBoard();

    return 0;
}
