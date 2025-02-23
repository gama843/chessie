#include "moveexecutor.hpp"
#include "movevalidator.hpp"

void MoveExecutor::makeMove(ChessEngine& engine, const Move& move, int player) {
    uint64_t fromBit = 1ULL << move.from;
    uint64_t toBit = 1ULL << move.to;

    // handle castling
    if ((move.from == 4 && move.to == 6 && MoveValidator::canCastleKingside(player, engine)) ||
        (move.from == 4 && move.to == 2 && MoveValidator::canCastleQueenside(player, engine)) ||
        (move.from == 60 && move.to == 62 && MoveValidator::canCastleKingside(player, engine)) ||
        (move.from == 60 && move.to == 58 && MoveValidator::canCastleQueenside(player, engine))) {
        if (player == 0) {
            // white castling
            if (move.to == 6) {
                // kingside castling
                removePiece(engine.whiteKing, 4);
                placePiece(engine.whiteKing, 6);
                removePiece(engine.whiteRooks, 7);
                placePiece(engine.whiteRooks, 5);
            } else {
                // queenside castling
                removePiece(engine.whiteKing, 4);
                placePiece(engine.whiteKing, 2);
                removePiece(engine.whiteRooks, 0);
                placePiece(engine.whiteRooks, 3);
            }
        } else {
            // black castling
            if (move.to == 62) {
                // kingside castling
                removePiece(engine.blackKing, 60);
                placePiece(engine.blackKing, 62);
                removePiece(engine.blackRooks, 63);
                placePiece(engine.blackRooks, 61);
            } else {
                // queenside castling
                removePiece(engine.blackKing, 60);
                placePiece(engine.blackKing, 58);
                removePiece(engine.blackRooks, 56);
                placePiece(engine.blackRooks, 59);
            }
        }
        return;
    }

    // handle en passant
    if (move.to == engine.getEnPassantTarget()) {
        int captureSquare = player == 0 ? move.to - 8 : move.to + 8;
        if (player == 0) {
            removePiece(engine.blackPawns, captureSquare);
        } else {
            removePiece(engine.whitePawns, captureSquare);
        }
    }

    // handle promotion
    if (move.promotion != '\0') {
        uint64_t& pawns = player == 0 ? engine.whitePawns : engine.blackPawns;
        uint64_t& promotedPiece = (move.promotion == 'q') ? (player == 0 ? engine.whiteQueens : engine.blackQueens) :
                                 (move.promotion == 'r') ? (player == 0 ? engine.whiteRooks : engine.blackRooks) :
                                 (move.promotion == 'b') ? (player == 0 ? engine.whiteBishops : engine.blackBishops) :
                                 (player == 0 ? engine.whiteKnights : engine.blackKnights);

        removePiece(pawns, move.from);
        placePiece(promotedPiece, move.to);
        return;
    }

    // remove any piece that is being captured
    removePiece(engine.whitePawns, move.to);
    removePiece(engine.whiteKnights, move.to);
    removePiece(engine.whiteBishops, move.to);
    removePiece(engine.whiteRooks, move.to);
    removePiece(engine.whiteQueens, move.to);
    removePiece(engine.whiteKing, move.to);
    removePiece(engine.blackPawns, move.to);
    removePiece(engine.blackKnights, move.to);
    removePiece(engine.blackBishops, move.to);
    removePiece(engine.blackRooks, move.to);
    removePiece(engine.blackQueens, move.to);
    removePiece(engine.blackKing, move.to);

    uint64_t pawns = player == 0 ? engine.whitePawns : engine.blackPawns;
    uint64_t knights = player == 0 ? engine.whiteKnights : engine.blackKnights;
    uint64_t bishops = player == 0 ? engine.whiteBishops : engine.blackBishops;
    uint64_t rooks = player == 0 ? engine.whiteRooks : engine.blackRooks;
    uint64_t queens = player == 0 ? engine.whiteQueens : engine.blackQueens;
    uint64_t king = player == 0 ? engine.whiteKing : engine.blackKing;

    if (pawns & fromBit) {
        removePiece(pawns, move.from);
        placePiece(pawns, move.to);
        if (player == 0) {
            engine.whitePawns = pawns;
        } else {
            engine.blackPawns = pawns;
        }
    } else if (knights & fromBit) {
        removePiece(knights, move.from);
        placePiece(knights, move.to);
        if (player == 0) {
            engine.whiteKnights = knights;
        } else {
            engine.blackKnights = knights;
        }
    } else if (bishops & fromBit) {
        removePiece(bishops, move.from);
        placePiece(bishops, move.to);
        if (player == 0) {
            engine.whiteBishops = bishops;
        } else {
            engine.blackBishops = bishops;
        }
    } else if (rooks & fromBit) {
        removePiece(rooks, move.from);
        placePiece(rooks, move.to);
        if (player == 0) {
            engine.whiteRooks = rooks;
        } else {
            engine.blackRooks = rooks;
        }
    } else if (queens & fromBit) {
        removePiece(queens, move.from);
        placePiece(queens, move.to);
        if (player == 0) {
            engine.whiteQueens = queens;
        } else {
            engine.blackQueens = queens;
        }
    } else if (king & fromBit) {
        removePiece(king, move.from);
        placePiece(king, move.to);
        if (player == 0) {
            engine.whiteKing = king;
        } else {
            engine.blackKing = king;
        }

        // update castling flags
        if (player == 0) {
            engine.whiteKingMoved = true;
        } else {
            engine.blackKingMoved = true;
        }
    }

    // update rook moved flags
    if (move.from == 0) engine.whiteRookA1Moved = true;
    if (move.from == 7) engine.whiteRookH1Moved = true;
    if (move.from == 56) engine.blackRookA8Moved = true;
    if (move.from == 63) engine.blackRookH8Moved = true;
}

void MoveExecutor::removePiece(uint64_t& bitboard, int square) {
    bitboard &= ~(1ULL << square);
}

void MoveExecutor::placePiece(uint64_t& bitboard, int square) {
    bitboard |= (1ULL << square);
}