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

void setupCastlingTest(ChessEngine& engine) {
    // clear the board for custom setup
    engine.whitePawns = 0;
    engine.whiteKnights = 0;
    engine.whiteBishops = 0;
    engine.whiteRooks = (1ULL << 0) | (1ULL << 7); // rooks at A1 and H1
    engine.whiteQueens = 0;
    engine.whiteKing = 1ULL << 4; // king at E1
    engine.blackPawns = 0;
    engine.blackKnights = 0;
    engine.blackBishops = 0;
    engine.blackRooks = (1ULL << 56) | (1ULL << 63); // rooks at A8 and H8
    engine.blackQueens = 0;
    engine.blackKing = 1ULL << 60; // king at E8

    engine.setWhiteKingMoved(false);
    engine.setWhiteRookA1Moved(false);
    engine.setWhiteRookH1Moved(false);
    engine.setBlackKingMoved(false);
    engine.setBlackRookA8Moved(false);
    engine.setBlackRookH8Moved(false);
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

    // initialize new game and setup for castling test
    engine.newGame();
    setupCastlingTest(engine);
    std::cout << "Board set up for castling test:" << std::endl;
    engine.printBoard();

    // test kingside castling for white
    Move kingsideCastleWhite(4, 6);
    if (engine.isValidMove(kingsideCastleWhite, 0)) {
        std::cout << "Kingside Castling for White is valid!" << std::endl;
        engine.makeMove(kingsideCastleWhite, 0);
        std::cout << "Board after Kingside Castling for White:" << std::endl;
        engine.printBoard();
    } else {
        std::cout << "Kingside Castling for White is invalid!" << std::endl;
    }

    // reset for next test
    engine.newGame();
    setupCastlingTest(engine);

    // test queenside castling for white
    Move queensideCastleWhite(4, 2);
    if (engine.isValidMove(queensideCastleWhite, 0)) {
        std::cout << "Queenside Castling for White is valid!" << std::endl;
        engine.makeMove(queensideCastleWhite, 0);
        std::cout << "Board after Queenside Castling for White:" << std::endl;
        engine.printBoard();
    } else {
        std::cout << "Queenside Castling for White is invalid!" << std::endl;
    }

    // reset for next test
    engine.newGame();
    setupCastlingTest(engine);

    // test kingside castling for black
    Move kingsideCastleBlack(60, 62);
    if (engine.isValidMove(kingsideCastleBlack, 1)) {
        std::cout << "Kingside Castling for Black is valid!" << std::endl;
        engine.makeMove(kingsideCastleBlack, 1);
        std::cout << "Board after Kingside Castling for Black:" << std::endl;
        engine.printBoard();
    } else {
        std::cout << "Kingside Castling for Black is invalid!" << std::endl;
    }

    // reset for next test
    engine.newGame();
    setupCastlingTest(engine);

    // test queenside castling for black
    Move queensideCastleBlack(60, 58);
    if (engine.isValidMove(queensideCastleBlack, 1)) {
        std::cout << "Queenside Castling for Black is valid!" << std::endl;
        engine.makeMove(queensideCastleBlack, 1);
        std::cout << "Board after Queenside Castling for Black:" << std::endl;
        engine.printBoard();
    } else {
        std::cout << "Queenside Castling for Black is invalid!" << std::endl;
    }

    return 0;
}