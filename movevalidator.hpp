#ifndef MOVEVALIDATOR_HPP
#define MOVEVALIDATOR_HPP

#include <cstdint>
#include "chessengine.hpp"

class MoveValidator {
public:
    static bool isValidPawnMove(const Move& move, int player, uint64_t pawns, uint64_t opponentPieces);
    static bool isValidKnightMove(const Move& move, int player, uint64_t knights, uint64_t ownPieces);
    static bool isValidBishopMove(const Move& move, int player, uint64_t bishops, uint64_t ownPieces, uint64_t occupied);
    static bool isValidRookMove(const Move& move, int player, uint64_t rooks, uint64_t ownPieces, uint64_t occupied);
    static bool isValidQueenMove(const Move& move, int player, uint64_t queens, uint64_t ownPieces, uint64_t occupied);
    static bool isValidKingMove(const Move& move, int player, uint64_t king, uint64_t ownPieces);
};

#endif // MOVEVALIDATOR_HPP