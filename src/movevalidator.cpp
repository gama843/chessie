#include "movevalidator.hpp"
#include "moveexecutor.hpp"
#include "movegenerator.hpp"
#include <iostream>
#include "utils.hpp"

bool MoveValidator::isValidMove(const Move& move, int player, const ChessEngine& engine) {
    if (!engine.isWithinBoard(move.from) || !engine.isWithinBoard(move.to)) {
        std::cout << "Move from " << move.from << " to " << move.to << " is out of bounds" << std::endl;
        return false;
    }

    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    uint64_t pawns = player == 0 ? engine.whitePawns : engine.blackPawns;
    uint64_t knights = player == 0 ? engine.whiteKnights : engine.blackKnights;
    uint64_t bishops = player == 0 ? engine.whiteBishops : engine.blackBishops;
    uint64_t rooks = player == 0 ? engine.whiteRooks : engine.blackRooks;
    uint64_t queens = player == 0 ? engine.whiteQueens : engine.blackQueens;
    uint64_t king = player == 0 ? engine.whiteKing : engine.blackKing;
    uint64_t ownPieces = player == 0 ? (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing)
                                     : (engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);
    uint64_t opponentPieces = player == 0 ? (engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing)
                                          : (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing);
    uint64_t occupied = (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing |
                         engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);

    bool valid = false;
    if (pawns & fromBit) {
        valid = isValidPawnMove(move, player, ownPieces, opponentPieces, engine.getEnPassantTarget());
    } else if (knights & fromBit) {
        valid = isValidKnightMove(move, player, knights, ownPieces);
    } else if (bishops & fromBit) {
        valid = isValidBishopMove(move, player, bishops, ownPieces, occupied);
    } else if (rooks & fromBit) {
        valid = isValidRookMove(move, player, rooks, ownPieces, occupied);
    } else if (queens & fromBit) {
        valid = isValidQueenMove(move, player, queens, ownPieces, occupied);
    } else if (king & fromBit) {
        // handle castling
        if ((move.from == 4 && move.to == 6 && canCastleKingside(player, engine)) ||
            (move.from == 4 && move.to == 2 && canCastleQueenside(player, engine)) ||
            (move.from == 60 && move.to == 62 && canCastleKingside(player, engine)) ||
            (move.from == 60 && move.to == 58 && canCastleQueenside(player, engine))) {
            return true;
        }
        valid = isValidKingMove(move, player, king, ownPieces);
    } else {
        std::cout << "No piece at from square" << std::endl;
        return false;
    }

    if (valid && !doesMoveExposeKing(move, player, engine)) {
        return true;
    }

    return false;
}

bool MoveValidator::isValidPawnMove(const Move& move, int player, uint64_t ownPieces, uint64_t opponentPieces, int enPassantTarget) {
    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    int direction = player == 0 ? 1 : -1;

    // single step forward
    if (move.to == move.from + 8 * direction && !(toBit & (opponentPieces | ownPieces))) {
        // promotion check
        if ((player == 0 && move.to >= 56) || (player == 1 && move.to <= 7)) {
            return move.promotion == 'q' || move.promotion == 'r' || move.promotion == 'b' || move.promotion == 'n';
        }
        return true;
    }

    // double step forward from the starting position
    if (move.to == move.from + 16 * direction && move.from / 8 == (player == 0 ? 1 : 6) &&
        !(toBit & (opponentPieces | ownPieces)) && !((1ULL << (move.from + 8 * direction)) & (opponentPieces | ownPieces))) {
        return true;
    }

    // capture move
    if ((move.to == move.from + 7 * direction || move.to == move.from + 9 * direction) && (toBit & opponentPieces)) {
        // promotion check
        if ((player == 0 && move.to >= 56) || (player == 1 && move.to <= 7)) {
            return move.promotion == 'q' || move.promotion == 'r' || move.promotion == 'b' || move.promotion == 'n';
        }
        return true;
    }

    // en passant move
    if ((move.to == enPassantTarget) && (move.from + 7 * direction == enPassantTarget || move.from + 9 * direction == enPassantTarget)) {
        return true;
    }

    return false;
}

bool MoveValidator::isValidKnightMove(const Move& move, int player, uint64_t knights, uint64_t ownPieces) {
    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    int rowDiff = abs((move.from / 8) - (move.to / 8));
    int colDiff = abs((move.from % 8) - (move.to % 8));

    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        if (!(toBit & ownPieces)) {
            return true;
        }
    }

    return false;
}

bool MoveValidator::isValidBishopMove(const Move& move, int player, uint64_t bishops, uint64_t ownPieces, uint64_t occupied) {
    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    int rowDiff = abs((move.from / 8) - (move.to / 8));
    int colDiff = abs((move.from % 8) - (move.to % 8));

    if (rowDiff == colDiff) {
        int direction = (move.to > move.from) ? 1 : -1;
        int step = (move.to > move.from) ? ((move.to % 8 > move.from % 8) ? 9 : 7) : ((move.to % 8 > move.from % 8) ? -7 : -9);

        for (int i = move.from + step; i != move.to; i += step) {
            if (occupied & (1ULL << i)) {
                return false;
            }
        }

        if (!(toBit & ownPieces)) {
            return true;
        }
    }

    return false;
}

bool MoveValidator::isValidRookMove(const Move& move, int player, uint64_t rooks, uint64_t ownPieces, uint64_t occupied) {
    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    int rowDiff = abs((move.from / 8) - (move.to / 8));
    int colDiff = abs((move.from % 8) - (move.to % 8));

    if (rowDiff == 0 || colDiff == 0) {
        int direction = (move.to > move.from) ? 1 : -1;
        int step = (colDiff == 0) ? 8 * direction : 1 * direction;

        for (int i = move.from + step; i != move.to; i += step) {
            if (occupied & (1ULL << i)) {
                return false;
            }
        }

        if (!(toBit & ownPieces)) {
            return true;
        }
    }

    return false;
}

bool MoveValidator::isValidQueenMove(const Move& move, int player, uint64_t queens, uint64_t ownPieces, uint64_t occupied) {
    return isValidBishopMove(move, player, queens, ownPieces, occupied) || isValidRookMove(move, player, queens, ownPieces, occupied);
}

bool MoveValidator::isValidKingMove(const Move& move, int player, uint64_t king, uint64_t ownPieces) {
    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    int rowDiff = abs((move.from / 8) - (move.to / 8));
    int colDiff = abs((move.from % 8) - (move.to % 8));

    if ((rowDiff <= 1 && colDiff <= 1) && !(toBit & ownPieces)) {
        return true;
    }

    return false;
}

bool MoveValidator::canCastleKingside(int player, const ChessEngine& engine) {
    if (player == 0) {
        return !engine.getWhiteKingMoved() && !engine.getWhiteRookH1Moved() &&
               !(engine.whitePawns & 0x0000000000000060) && // ensure no pieces on F1 and G1
               !(engine.whiteKnights & 0x0000000000000060) &&
               !(engine.whiteBishops & 0x0000000000000060) &&
               !(engine.whiteRooks & 0x0000000000000060) &&
               !(engine.whiteQueens & 0x0000000000000060) &&
               !(engine.whiteKing & 0x0000000000000060);
    } else {
        return !engine.getBlackKingMoved() && !engine.getBlackRookH8Moved() &&
               !(engine.blackPawns & 0x6000000000000000) && // ensure no pieces on F8 and G8
               !(engine.blackKnights & 0x6000000000000000) &&
               !(engine.blackBishops & 0x6000000000000000) &&
               !(engine.blackRooks & 0x6000000000000000) &&
               !(engine.blackQueens & 0x6000000000000000) &&
               !(engine.blackKing & 0x6000000000000000);
    }
}

bool MoveValidator::canCastleQueenside(int player, const ChessEngine& engine) {
    if (player == 0) {
        return !engine.getWhiteKingMoved() && !engine.getWhiteRookA1Moved() &&
               !(engine.whitePawns & 0x000000000000000E) && // ensure no pieces on B1, C1, D1
               !(engine.whiteKnights & 0x000000000000000E) &&
               !(engine.whiteBishops & 0x000000000000000E) &&
               !(engine.whiteRooks & 0x000000000000000E) &&
               !(engine.whiteQueens & 0x000000000000000E) &&
               !(engine.whiteKing & 0x000000000000000E);
    } else {
        return !engine.getBlackKingMoved() && !engine.getBlackRookA8Moved() &&
               !(engine.blackPawns & 0x0E00000000000000) && // ensure no pieces on B8, C8, D8
               !(engine.blackKnights & 0x0E00000000000000) &&
               !(engine.blackBishops & 0x0E00000000000000) &&
               !(engine.blackRooks & 0x0E00000000000000) &&
               !(engine.blackQueens & 0x0E00000000000000) &&
               !(engine.blackKing & 0x0E00000000000000);
    }
}

bool MoveValidator::doesMoveExposeKing(const Move& move, int player, const ChessEngine& engine) {
    ChessEngine testEngine = engine;
    MoveExecutor::makeMove(testEngine, move, player);

    // find the king's position
    uint64_t kingPosition = player == 0 ? testEngine.whiteKing : testEngine.blackKing;
    int kingSquare = __builtin_ffsll(kingPosition) - 1;

    // generate all opponent moves
    std::vector<Move> opponentMoves = testEngine.generateAllPossibleMoves(1 - player);
    for (const Move& opponentMove : opponentMoves) {
        if (opponentMove.to == kingSquare) {
            return true;
        }
    }
    return false;
}

bool MoveValidator::isSquareAttacked(const ChessEngine& engine, int square, int attacker) {
    uint64_t attackMask = 0;

    // generate attack mask for the opponent
    std::vector<Move> opponentMoves = MoveGenerator::generateAllMoves(engine, attacker);
    for (const Move& move : opponentMoves) {
        attackMask |= (1ULL << move.to);
    }

    return attackMask & (1ULL << square);
}