#include "movegenerator.hpp"

uint64_t MoveGenerator::generatePawnMoves(uint64_t pawns, bool isWhite) {
    uint64_t singleStep, captures;
    if (isWhite) {
        singleStep = (pawns << 8) & ~0xFF00000000000000; // one square forward, clear 8th rank
        captures = ((pawns & ~0x8080808080808080) << 7) | ((pawns & ~0x0101010101010101) << 9); // diagonal captures
    } else {
        singleStep = (pawns >> 8) & ~0x00000000000000FF; // one square forward, clear 1st rank
        captures = ((pawns & ~0x0101010101010101) >> 7) | ((pawns & ~0x8080808080808080) >> 9); // diagonal captures
    }
    return singleStep | captures;
}

uint64_t MoveGenerator::generateKnightMoves(uint64_t knights) {
    uint64_t moves = 0;
    uint64_t l1 = (knights >> 1) & 0x7F7F7F7F7F7F7F7F;
    uint64_t l2 = (knights >> 2) & 0x3F3F3F3F3F3F3F3F;
    uint64_t r1 = (knights << 1) & 0xFEFEFEFEFEFEFEFE;
    uint64_t r2 = (knights << 2) & 0xFCFCFCFCFCFCFCFC;

    moves |= (l2 | r2) << 8;
    moves |= (l2 | r2) >> 8;
    moves |= (l1 | r1) << 16;
    moves |= (l1 | r1) >> 16;

    return moves;
}

uint64_t MoveGenerator::generateBishopMoves(uint64_t bishops, uint64_t occupied) {
    // placeholder for generating bishop moves
    return 0;
}

uint64_t MoveGenerator::generateRookMoves(uint64_t rooks, uint64_t occupied) {
    // placeholder for generating rook moves
    return 0;
}

uint64_t MoveGenerator::generateQueenMoves(uint64_t queens, uint64_t occupied) {
    // queen moves are a combination of bishop and rook moves
    return generateBishopMoves(queens, occupied) | generateRookMoves(queens, occupied);
}

uint64_t MoveGenerator::generateKingMoves(uint64_t king) {
    uint64_t moves = 0;
    moves |= (king << 1) & 0xFEFEFEFEFEFEFEFE;
    moves |= (king >> 1) & 0x7F7F7F7F7F7F7F7F;
    moves |= (king << 8);
    moves |= (king >> 8);
    moves |= (king << 9) & 0xFEFEFEFEFEFEFEFE;
    moves |= (king >> 9) & 0x7F7F7F7F7F7F7F7F;
    moves |= (king << 7) & 0x7F7F7F7F7F7F7F7F;
    moves |= (king >> 7) & 0xFEFEFEFEFEFEFEFE;
    return moves;
}