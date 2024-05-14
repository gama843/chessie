#include "movevalidator.hpp"

bool MoveValidator::isValidPawnMove(const Move& move, int player, uint64_t pawns, uint64_t opponentPieces) {
    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    // Define the direction based on the player
    int direction = player == 0 ? 1 : -1;

    // Single step forward
    if (move.to == move.from + 8 * direction && !(toBit & opponentPieces) && !(toBit & pawns)) {
        return true;
    }

    // Double step forward from the starting position
    if (move.to == move.from + 16 * direction && move.from / 8 == (player == 0 ? 1 : 6) && !(toBit & opponentPieces) && !(toBit & pawns)) {
        return true;
    }

    // Capture move
    if ((move.to == move.from + 7 * direction || move.to == move.from + 9 * direction) && (toBit & opponentPieces)) {
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
        int step = (colDiff == 1) ? 9 * direction : 7 * direction;

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