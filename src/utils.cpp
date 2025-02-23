#include "utils.hpp"
#include "movegenerator.hpp"
#include "movevalidator.hpp"
#include <iostream>
#include <fstream>
#include <bitset>

void Utils::printBoard(const ChessEngine& engine) {
    char pieceChars[2][6] = {
        {'P', 'N', 'B', 'R', 'Q', 'K'}, // white pieces
        {'p', 'n', 'b', 'r', 'q', 'k'}  // black pieces
    };

    uint64_t pieces[2][6] = {
        {engine.whitePawns, engine.whiteKnights, engine.whiteBishops, engine.whiteRooks, engine.whiteQueens, engine.whiteKing},
        {engine.blackPawns, engine.blackKnights, engine.blackBishops, engine.blackRooks, engine.blackQueens, engine.blackKing}
    };

    std::cout << "  a b c d e f g h" << std::endl;
    for (int rank = 7; rank >= 0; --rank) {
        std::cout << rank + 1 << " ";
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            bool empty = true;
            for (int color = 0; color < 2; ++color) {
                for (int piece = 0; piece < 6; ++piece) {
                    if (pieces[color][piece] & (1ULL << square)) {
                        std::cout << pieceChars[color][piece] << " ";
                        empty = false;
                        break;
                    }
                }
                if (!empty) break;
            }
            if (empty) {
                std::cout << ". ";
            }
        }
        std::cout << rank + 1 << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
    std::cout << std::endl;
}

void Utils::printBitboard(uint64_t bitboard) {
    std::bitset<64> b(bitboard);
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            std::cout << b[rank * 8 + file] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int Utils::evaluateBoard(const ChessEngine& engine, int player) {
    const int pawnValue = 1;
    const int knightValue = 3;
    const int bishopValue = 3;
    const int rookValue = 5;
    const int queenValue = 9;

    int whiteScore = 0;
    int blackScore = 0;

    whiteScore += __builtin_popcountll(engine.whitePawns) * pawnValue;
    whiteScore += __builtin_popcountll(engine.whiteKnights) * knightValue;
    whiteScore += __builtin_popcountll(engine.whiteBishops) * bishopValue;
    whiteScore += __builtin_popcountll(engine.whiteRooks) * rookValue;
    whiteScore += __builtin_popcountll(engine.whiteQueens) * queenValue;

    blackScore += __builtin_popcountll(engine.blackPawns) * pawnValue;
    blackScore += __builtin_popcountll(engine.blackKnights) * knightValue;
    blackScore += __builtin_popcountll(engine.blackBishops) * bishopValue;
    blackScore += __builtin_popcountll(engine.blackRooks) * rookValue;
    blackScore += __builtin_popcountll(engine.blackQueens) * queenValue;

    // return the evaluation from the perspective of the player
    return (player == 0) ? (whiteScore - blackScore) : (blackScore - whiteScore);
}

std::string Utils::getGameStatus(const ChessEngine& engine, int player) {
    if (engine.getGameStatus() == GameStatus::BLACK_RESIGNS) {
        return "Black resigns";
    } else if (engine.getGameStatus() == GameStatus::WHITE_RESIGNS) {
        return "White resigns";
    }

    int opponent = 1 - player;
    std::vector<Move> opponentMoves = MoveGenerator::generateAllValidMoves(engine, opponent);
    
    if (opponentMoves.empty()) {
        // check if the opponent's king is in check
        uint64_t opponentKing = (opponent == 0) ? engine.whiteKing : engine.blackKing;
        int kingPosition = __builtin_ffsll(opponentKing) - 1;

        if (MoveValidator::isSquareAttacked(engine, kingPosition, player)) {
            return (player == 0) ? "Black is checkmated" : "White is checkmated";
        } else {
            return "Stalemate";
        }
    }

    if (Utils::isInsufficientMaterial(engine)) {
        return "Insufficient material";
    }

    if (engine.isRepetitionDraw()) {
        return "Threefold repetition";
    }

    if (engine.isFiftyMoveDraw()) {
        return "Fifty move draw";
    }

    return "Game in progress";
}

void Utils::printHelp() {
    std::cout << "The software provides basic chess engine functionality such as recording your games, "
              << "playing for a single or both players, checking the validity of a move or evaluating a player's position. "
              << "You can run it interactively, use it to automate some chess-related workflow or even use it as a simple opponent. "
              << "You can run the program with several arguments:\n"
              << "-n --new    For a new game session.\n"
              << "-f --file   The path to the input game file. Please note that if the game is finished the program will \n"
              << "-l --log    The path to the output log file.\n"
              << "-e --eval   Returns evaluation of a player's position based on the provided ID - 0 = white, 1 = black.\n";
}

std::string Utils::positionToUCI(int position) {
    char file = 'a' + (position % 8);
    char rank = '1' + (position / 8);
    return std::string(1, file) + std::string(1, rank);
}


void Utils::printMoves(const std::vector<Move>& moves) {
    for (const Move& move : moves) {
        std::cout << "Move: " << Utils::positionToUCI(move.from) << Utils::positionToUCI(move.to) << std::endl;
    }
}

bool Utils::isInsufficientMaterial(const ChessEngine& engine) {
    int whitePawnCount = __builtin_popcountll(engine.whitePawns);
    int whiteKnightCount = __builtin_popcountll(engine.whiteKnights);
    int whiteBishopCount = __builtin_popcountll(engine.whiteBishops);
    int whiteRookCount = __builtin_popcountll(engine.whiteRooks);
    int whiteQueenCount = __builtin_popcountll(engine.whiteQueens);

    int blackPawnCount = __builtin_popcountll(engine.blackPawns);
    int blackKnightCount = __builtin_popcountll(engine.blackKnights);
    int blackBishopCount = __builtin_popcountll(engine.blackBishops);
    int blackRookCount = __builtin_popcountll(engine.blackRooks);
    int blackQueenCount = __builtin_popcountll(engine.blackQueens);

    // check if there are any pawns, rooks, or queens on the board
    if (whitePawnCount > 0 || blackPawnCount > 0 || whiteRookCount > 0 || blackRookCount > 0 ||
        whiteQueenCount > 0 || blackQueenCount > 0) {
        return false;
    }

    // king vs. king
    if (whitePawnCount + whiteKnightCount + whiteBishopCount + whiteRookCount + whiteQueenCount == 0 &&
        blackPawnCount + blackKnightCount + blackBishopCount + blackRookCount + blackQueenCount == 0) {
        return true;
    }

    // king and single minor piece (knight or bishop) vs. king
    if ((whitePawnCount == 0 && whiteRookCount == 0 && whiteQueenCount == 0 &&
         blackPawnCount == 0 && blackRookCount == 0 && blackQueenCount == 0) &&
        ((whiteKnightCount + whiteBishopCount == 1 && blackKnightCount + blackBishopCount == 0) ||
         (whiteKnightCount + whiteBishopCount == 0 && blackKnightCount + blackBishopCount == 1))) {
        return true;
    }

    // king and bishop vs. king and bishop (same color bishops)
    if (whitePawnCount == 0 && whiteKnightCount == 0 && whiteRookCount == 0 && whiteQueenCount == 0 &&
        blackPawnCount == 0 && blackKnightCount == 0 && blackRookCount == 0 && blackQueenCount == 0 &&
        whiteBishopCount == 1 && blackBishopCount == 1) {
        
        // check if both bishops are on the same color
        int whiteBishopSquare = __builtin_ffsll(engine.whiteBishops) - 1;
        int blackBishopSquare = __builtin_ffsll(engine.blackBishops) - 1;
        
        bool whiteBishopColor = (whiteBishopSquare / 8 + whiteBishopSquare % 8) % 2;
        bool blackBishopColor = (blackBishopSquare / 8 + blackBishopSquare % 8) % 2;

        if (whiteBishopColor == blackBishopColor) {
            return true;
        }
    }

    // king and two knights vs. king
    if (whitePawnCount == 0 && whiteBishopCount == 0 && whiteRookCount == 0 && whiteQueenCount == 0 &&
        blackPawnCount == 0 && blackBishopCount == 0 && blackRookCount == 0 && blackQueenCount == 0 &&
        ((whiteKnightCount == 2 && blackKnightCount == 0) || (whiteKnightCount == 0 && blackKnightCount == 2))) {
        return true;
    }

    return false;
}