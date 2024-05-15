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

    whiteKingMoved = whiteRookA1Moved = whiteRookH1Moved = false;
    blackKingMoved = blackRookA8Moved = blackRookH8Moved = false;
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
    // placeholder for checking the game status (e.g., checkmate, stalemate)
    return "Game in progress";
}

bool ChessEngine::isValidMove(const Move& move, int player) {
    if (!isWithinBoard(move.from) || !isWithinBoard(move.to)) {
        std::cout << "Move from " << move.from << " to " << move.to << " is out of bounds" << std::endl;
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
        // handle castling
        if ((move.from == 4 && move.to == 6 && canCastleKingside(player)) ||
            (move.from == 4 && move.to == 2 && canCastleQueenside(player)) ||
            (move.from == 60 && move.to == 62 && canCastleKingside(player)) ||
            (move.from == 60 && move.to == 58 && canCastleQueenside(player))) {
            return true;
        }
        return MoveValidator::isValidKingMove(move, player, king, ownPieces);
    }

    std::cout << "No piece at from square" << std::endl;
    return false;
}

void ChessEngine::makeMove(const Move& move, int player) {
    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    // handle castling
    if ((move.from == 4 && move.to == 6 && canCastleKingside(0)) ||
        (move.from == 4 && move.to == 2 && canCastleQueenside(0)) ||
        (move.from == 60 && move.to == 62 && canCastleKingside(1)) ||
        (move.from == 60 && move.to == 58 && canCastleQueenside(1))) {
        if (player == 0) {
            // white castling
            if (move.to == 6) {
                // kingside castling
                removePiece(whiteKing, 4);
                placePiece(whiteKing, 6);
                removePiece(whiteRooks, 7);
                placePiece(whiteRooks, 5);
            } else {
                // queenside castling
                removePiece(whiteKing, 4);
                placePiece(whiteKing, 2);
                removePiece(whiteRooks, 0);
                placePiece(whiteRooks, 3);
            }
        } else {
            // black castling
            if (move.to == 62) {
                // kingside castling
                removePiece(blackKing, 60);
                placePiece(blackKing, 62);
                removePiece(blackRooks, 63);
                placePiece(blackRooks, 61);
            } else {
                // queenside castling
                removePiece(blackKing, 60);
                placePiece(blackKing, 58);
                removePiece(blackRooks, 56);
                placePiece(blackRooks, 59);
            }
        }
        return;
    }

    // remove any piece that is being captured
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

        // update castling flags
        if (player == 0) {
            whiteKingMoved = true;
        } else {
            blackKingMoved = true;
        }
    }

    // update rook moved flags
    if (move.from == 0) whiteRookA1Moved = true;
    if (move.from == 7) whiteRookH1Moved = true;
    if (move.from == 56) blackRookA8Moved = true;
    if (move.from == 63) blackRookH8Moved = true;
}

bool ChessEngine::canCastleKingside(int player) {
    if (player == 0) {
        std::cout << "Checking kingside castling for white...\n";
        if (whiteKingMoved) std::cout << "White King has moved\n";
        if (whiteRookH1Moved) std::cout << "White H1 Rook has moved\n";
        if (whiteRooks & 0x0000000000000080) std::cout << "White Rook on H1 is in position\n";
        if (whiteKing & 0x0000000000000010) std::cout << "White King is in position\n";
        std::cout << "Squares between king and rook:\n";
        std::cout << "F1: " << ((whitePawns & 0x0000000000000020) || (whiteKnights & 0x0000000000000020) || 
                                (whiteBishops & 0x0000000000000020) || (whiteRooks & 0x0000000000000020) || 
                                (whiteQueens & 0x0000000000000020) || (whiteKing & 0x0000000000000020)) << "\n";
        std::cout << "G1: " << ((whitePawns & 0x0000000000000040) || (whiteKnights & 0x0000000000000040) || 
                                (whiteBishops & 0x0000000000000040) || (whiteRooks & 0x0000000000000040) || 
                                (whiteQueens & 0x0000000000000040) || (whiteKing & 0x0000000000000040)) << "\n";

        return !whiteKingMoved && !whiteRookH1Moved &&
               !(whitePawns & 0x0000000000000060) && // ensure no pieces on F1 and G1
               !(whiteKnights & 0x0000000000000060) &&
               !(whiteBishops & 0x0000000000000060) &&
               !(whiteRooks & 0x0000000000000060) &&
               !(whiteQueens & 0x0000000000000060) &&
               !(whiteKing & 0x0000000000000060);
    } else {
        std::cout << "Checking kingside castling for black...\n";
        if (blackKingMoved) std::cout << "Black King has moved\n";
        if (blackRookH8Moved) std::cout << "Black H8 Rook has moved\n";
        if (blackRooks & 0x8000000000000000) std::cout << "Black Rook on H8 is in position\n";
        if (blackKing & 0x1000000000000000) std::cout << "Black King is in position\n";
        std::cout << "Squares between king and rook:\n";
        std::cout << "F8: " << ((blackPawns & 0x2000000000000000) || (blackKnights & 0x2000000000000000) || 
                                (blackBishops & 0x2000000000000000) || (blackRooks & 0x2000000000000000) || 
                                (blackQueens & 0x2000000000000000) || (blackKing & 0x2000000000000000)) << "\n";
        std::cout << "G8: " << ((blackPawns & 0x4000000000000000) || (blackKnights & 0x4000000000000000) || 
                                (blackBishops & 0x4000000000000000) || (blackRooks & 0x4000000000000000) || 
                                (blackQueens & 0x4000000000000000) || (blackKing & 0x4000000000000000)) << "\n";

        return !blackKingMoved && !blackRookH8Moved &&
               !(blackPawns & 0x6000000000000000) && // ensure no pieces on F8 and G8
               !(blackKnights & 0x6000000000000000) &&
               !(blackBishops & 0x6000000000000000) &&
               !(blackRooks & 0x6000000000000000) &&
               !(blackQueens & 0x6000000000000000) &&
               !(blackKing & 0x6000000000000000);
    }
}

bool ChessEngine::canCastleQueenside(int player) {
    if (player == 0) {
        std::cout << "Checking queenside castling for white...\n";
        if (whiteKingMoved) std::cout << "White King has moved\n";
        if (whiteRookA1Moved) std::cout << "White A1 Rook has moved\n";
        if (whiteRooks & 0x0000000000000001) std::cout << "White Rook on A1 is in position\n";
        if (whiteKing & 0x0000000000000010) std::cout << "White King is in position\n";
        std::cout << "Squares between king and rook:\n";
        std::cout << "B1: " << ((whitePawns & 0x0000000000000002) || (whiteKnights & 0x0000000000000002) || 
                                (whiteBishops & 0x0000000000000002) || (whiteRooks & 0x0000000000000002) || 
                                (whiteQueens & 0x0000000000000002) || (whiteKing & 0x0000000000000002)) << "\n";
        std::cout << "C1: " << ((whitePawns & 0x0000000000000004) || (whiteKnights & 0x0000000000000004) || 
                                (whiteBishops & 0x0000000000000004) || (whiteRooks & 0x0000000000000004) || 
                                (whiteQueens & 0x0000000000000004) || (whiteKing & 0x0000000000000004)) << "\n";
        std::cout << "D1: " << ((whitePawns & 0x0000000000000008) || (whiteKnights & 0x0000000000000008) || 
                                (whiteBishops & 0x0000000000000008) || (whiteRooks & 0x0000000000000008) || 
                                (whiteQueens & 0x0000000000000008) || (whiteKing & 0x0000000000000008)) << "\n";

        return !whiteKingMoved && !whiteRookA1Moved &&
               !(whitePawns & 0x000000000000000E) && // ensure no pieces on B1, C1, D1
               !(whiteKnights & 0x000000000000000E) &&
               !(whiteBishops & 0x000000000000000E) &&
               !(whiteRooks & 0x000000000000000E) &&
               !(whiteQueens & 0x000000000000000E) &&
               !(whiteKing & 0x000000000000000E);
    } else {
        std::cout << "Checking queenside castling for black...\n";
        if (blackKingMoved) std::cout << "Black King has moved\n";
        if (blackRookA8Moved) std::cout << "Black A8 Rook has moved\n";
        if (blackRooks & 0x0100000000000000) std::cout << "Black Rook on A8 is in position\n";
        if (blackKing & 0x1000000000000000) std::cout << "Black King is in position\n";
        std::cout << "Squares between king and rook:\n";
        std::cout << "B8: " << ((blackPawns & 0x0200000000000000) || (blackKnights & 0x0200000000000000) || 
                                (blackBishops & 0x0200000000000000) || (blackRooks & 0x0200000000000000) || 
                                (blackQueens & 0x0200000000000000) || (blackKing & 0x0200000000000000)) << "\n";
        std::cout << "C8: " << ((blackPawns & 0x0400000000000000) || (blackKnights & 0x0400000000000000) || 
                                (blackBishops & 0x0400000000000000) || (blackRooks & 0x0400000000000000) || 
                                (blackQueens & 0x0400000000000000) || (blackKing & 0x0400000000000000)) << "\n";
        std::cout << "D8: " << ((blackPawns & 0x0800000000000000) || (blackKnights & 0x0800000000000000) || 
                                (blackBishops & 0x0800000000000000) || (blackRooks & 0x0800000000000000) || 
                                (blackQueens & 0x0800000000000000) || (blackKing & 0x0800000000000000)) << "\n";

        return !blackKingMoved && !blackRookA8Moved &&
               !(blackPawns & 0x0E00000000000000) && // ensure no pieces on B8, C8, D8
               !(blackKnights & 0x0E00000000000000) &&
               !(blackBishops & 0x0E00000000000000) &&
               !(blackRooks & 0x0E00000000000000) &&
               !(blackQueens & 0x0E00000000000000) &&
               !(blackKing & 0x0E00000000000000);
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

    // return the evaluation from the perspective of the player
    return (player == 0) ? (whiteScore - blackScore) : (blackScore - whiteScore);
}

Move ChessEngine::makeNaiveMove(int player) {
    // placeholder for making a naive move
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
        {'P', 'N', 'B', 'R', 'Q', 'K'}, // white pieces
        {'p', 'n', 'b', 'r', 'q', 'k'}  // black pieces
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

// getter and setter methods for castling flags
bool ChessEngine::getWhiteKingMoved() const { return whiteKingMoved; }
void ChessEngine::setWhiteKingMoved(bool moved) { whiteKingMoved = moved; }
bool ChessEngine::getWhiteRookA1Moved() const { return whiteRookA1Moved; }
void ChessEngine::setWhiteRookA1Moved(bool moved) { whiteRookA1Moved = moved; }
bool ChessEngine::getWhiteRookH1Moved() const { return whiteRookH1Moved; }
void ChessEngine::setWhiteRookH1Moved(bool moved) { whiteRookH1Moved = moved; }
bool ChessEngine::getBlackKingMoved() const { return blackKingMoved; }
void ChessEngine::setBlackKingMoved(bool moved) { blackKingMoved = moved; }
bool ChessEngine::getBlackRookA8Moved() const { return blackRookA8Moved; }
void ChessEngine::setBlackRookA8Moved(bool moved) { blackRookA8Moved = moved; }
bool ChessEngine::getBlackRookH8Moved() const { return blackRookH8Moved; }
void ChessEngine::setBlackRookH8Moved(bool moved) { blackRookH8Moved = moved; }