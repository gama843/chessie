#include "chessengine.hpp"
#include "movevalidator.hpp"
#include <iostream>
#include <bitset>
#include <fstream>

ChessEngine::ChessEngine() {
    newGame();
}

void ChessEngine::newGame() {
    whitePawns = 0x000000000000FF00;
    whiteKnights = 0x0000000000000042;
    whiteBishops = 0x0000000000000024;
    whiteRooks = 0x0000000000000081;
    whiteQueens = 0x0000000000000008;
    whiteKing = 0x0000000000000010;
    blackPawns = 0x00FF000000000000;
    blackKnights = 0x4200000000000000;
    blackBishops = 0x2400000000000000;
    blackRooks = 0x8100000000000000;
    blackQueens = 0x0800000000000000;
    blackKing = 0x1000000000000000;
}

void ChessEngine::loadGameFromFile(const std::string& path) {
    std::ifstream file(path);
    if (file.is_open()) {
        file >> whitePawns >> whiteKnights >> whiteBishops >> whiteRooks >> whiteQueens >> whiteKing;
        file >> blackPawns >> blackKnights >> blackBishops >> blackRooks >> blackQueens >> blackKing;
        file.close();
    }
}

void ChessEngine::saveGameToFile(const std::string& path) {
    std::ofstream file(path);
    if (file.is_open()) {
        file << whitePawns << ' ' << whiteKnights << ' ' << whiteBishops << ' ' << whiteRooks << ' ';
        file << whiteQueens << ' ' << whiteKing << '\n';
        file << blackPawns << ' ' << blackKnights << ' ' << blackBishops << ' ' << blackRooks << ' ';
        file << blackQueens << ' ' << blackKing << '\n';
        file.close();
    }
}

std::string ChessEngine::getGameStatus() {
    // Placeholder for checking the game status (e.g., checkmate, stalemate)
    return "Game in progress";
}

bool ChessEngine::isValidMove(const Move& move, int player) {
    if (!isWithinBoard(move.from) || !isWithinBoard(move.to)) {
        return false;
    }

    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    uint64_t pawns = player == 0 ? whitePawns : blackPawns;
    uint64_t knights = player == 0 ? whiteKnights : blackKnights;
    uint64_t bishops = player == 0 ? whiteBishops : blackBishops;
    uint64_t rooks = player == 0 ? whiteRooks : blackRooks;
    uint64_t queens = player == 0 ? whiteQueens : blackQueens;
    uint64_t king = player == 0 ? whiteKing : blackKing;
    uint64_t ownPieces = player == 0 ? (whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing)
                                     : (blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing);
    uint64_t opponentPieces = player == 0 ? (blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing)
                                          : (whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing);
    uint64_t occupied = (whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing |
                         blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing);

    if (pawns & fromBit) {
        return MoveValidator::isValidPawnMove(move, player, pawns, opponentPieces);
    } else if (knights & fromBit) {
        return MoveValidator::isValidKnightMove(move, player, knights, ownPieces);
    } else if (bishops & fromBit) {
        return MoveValidator::isValidBishopMove(move, player, bishops, ownPieces, occupied);
    } else if (rooks & fromBit) {
        return MoveValidator::isValidRookMove(move, player, rooks, ownPieces, occupied);
    } else if (queens & fromBit) {
        return MoveValidator::isValidQueenMove(move, player, queens, ownPieces, occupied);
    } else if (king & fromBit) {
        return MoveValidator::isValidKingMove(move, player, king, ownPieces);
    }

    return false;
}

void ChessEngine::makeMove(const Move& move, int player) {
    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    // Remove any piece that is being captured
    removePiece(whitePawns, move.to);
    removePiece(whiteKnights, move.to);
    removePiece(whiteBishops, move.to);
    removePiece(whiteRooks, move.to);
    removePiece(whiteQueens, move.to);
    removePiece(whiteKing, move.to);
    removePiece(blackPawns, move.to);
    removePiece(blackKnights, move.to);
    removePiece(blackBishops, move.to);
    removePiece(blackRooks, move.to);
    removePiece(blackQueens, move.to);
    removePiece(blackKing, move.to);

    uint64_t pawns = player == 0 ? whitePawns : blackPawns;
    uint64_t knights = player == 0 ? whiteKnights : blackKnights;
    uint64_t bishops = player == 0 ? whiteBishops : blackBishops;
    uint64_t rooks = player == 0 ? whiteRooks : blackRooks;
    uint64_t queens = player == 0 ? whiteQueens : blackQueens;
    uint64_t king = player == 0 ? whiteKing : blackKing;

    if (pawns & fromBit) {
        removePiece(pawns, move.from);
        placePiece(pawns, move.to);
        if (player == 0) {
            whitePawns = pawns;
        } else {
            blackPawns = pawns;
        }
    } else if (knights & fromBit) {
        removePiece(knights, move.from);
        placePiece(knights, move.to);
        if (player == 0) {
            whiteKnights = knights;
        } else {
            blackKnights = knights;
        }
    } else if (bishops & fromBit) {
        removePiece(bishops, move.from);
        placePiece(bishops, move.to);
        if (player == 0) {
            whiteBishops = bishops;
        } else {
            blackBishops = bishops;
        }
    } else if (rooks & fromBit) {
        removePiece(rooks, move.from);
        placePiece(rooks, move.to);
        if (player == 0) {
            whiteRooks = rooks;
        } else {
            blackRooks = rooks;
        }
    } else if (queens & fromBit) {
        removePiece(queens, move.from);
        placePiece(queens, move.to);
        if (player == 0) {
            whiteQueens = queens;
        } else {
            blackQueens = queens;
        }
    } else if (king & fromBit) {
        removePiece(king, move.from);
        placePiece(king, move.to);
        if (player == 0) {
            whiteKing = king;
        } else {
            blackKing = king;
        }
    }
}

void ChessEngine::removePiece(uint64_t& bitboard, int square) {
    bitboard &= ~(1ULL << square);
}

void ChessEngine::placePiece(uint64_t& bitboard, int square) {
    bitboard |= (1ULL << square);
}

int ChessEngine::getCurrentValue(int player) {
    const int pawnValue = 1;
    const int knightValue = 3;
    const int bishopValue = 3;
    const int rookValue = 5;
    const int queenValue = 9;

    int whiteScore = 0;
    int blackScore = 0;

    whiteScore += __builtin_popcountll(whitePawns) * pawnValue;
    whiteScore += __builtin_popcountll(whiteKnights) * knightValue;
    whiteScore += __builtin_popcountll(whiteBishops) * bishopValue;
    whiteScore += __builtin_popcountll(whiteRooks) * rookValue;
    whiteScore += __builtin_popcountll(whiteQueens) * queenValue;

    blackScore += __builtin_popcountll(blackPawns) * pawnValue;
    blackScore += __builtin_popcountll(blackKnights) * knightValue;
    blackScore += __builtin_popcountll(blackBishops) * bishopValue;
    blackScore += __builtin_popcountll(blackRooks) * rookValue;
    blackScore += __builtin_popcountll(blackQueens) * queenValue;

    return (player == 0) ? whiteScore - blackScore : blackScore - whiteScore;
}

Move ChessEngine::makeNaiveMove(int player) {
    // Placeholder for making a naive move
    return Move(0, 0);
}

void ChessEngine::printBitboard(uint64_t bitboard) {
    std::bitset<64> b(bitboard);
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            std::cout << b[rank * 8 + file] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ChessEngine::printBoard() {
    char pieceChars[2][6] = {
        {'P', 'N', 'B', 'R', 'Q', 'K'}, // White pieces
        {'p', 'n', 'b', 'r', 'q', 'k'}  // Black pieces
    };

    uint64_t pieces[2][6] = {
        {whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens, whiteKing},
        {blackPawns, blackKnights, blackBishops, blackRooks, blackQueens, blackKing}
    };

    for (int rank = 7; rank >= 0; --rank) {
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
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool ChessEngine::isWithinBoard(int square) {
    return square >= 0 && square < 64;
}