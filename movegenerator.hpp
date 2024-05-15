#ifndef MOVE_GENERATOR_HPP
#define MOVE_GENERATOR_HPP

#include <cstdint>

class MoveGenerator {
public:
    static uint64_t generatePawnMoves(uint64_t pawns, bool isWhite);
    static uint64_t generateKnightMoves(uint64_t knights);
    static uint64_t generateBishopMoves(uint64_t bishops, uint64_t occupied);
    static uint64_t generateRookMoves(uint64_t rooks, uint64_t occupied);
    static uint64_t generateQueenMoves(uint64_t queens, uint64_t occupied);
    static uint64_t generateKingMoves(uint64_t king);
};

#endif // MOVE_GENERATOR_HPP