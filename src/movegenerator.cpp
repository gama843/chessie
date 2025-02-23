#include "movegenerator.hpp"
#include "movevalidator.hpp"
#include "utils.hpp"
#include <unordered_set>

std::vector<Move> MoveGenerator::generateAllValidMoves(const ChessEngine& engine, int player) {
    std::vector<Move> allMoves = generateAllMoves(engine, player);

    for (auto it = allMoves.begin(); it != allMoves.end();) {
        if (!MoveValidator::isValidMove(*it, player, engine)) {
            it = allMoves.erase(it);
        } else {
            ++it;
        }
    }

    return allMoves;
}

std::vector<Move> MoveGenerator::generateAllMoves(const ChessEngine& engine, int player) {
    std::unordered_set<std::string> uniqueMoves;
    std::vector<Move> allMoves;

    std::vector<Move> pawnMoves = generatePawnMoves(engine, player);
    std::vector<Move> knightMoves = generateKnightMoves(engine, player);
    std::vector<Move> bishopMoves = generateBishopMoves(engine, player);
    std::vector<Move> rookMoves = generateRookMoves(engine, player);
    std::vector<Move> queenMoves = generateQueenMoves(engine, player);
    std::vector<Move> kingMoves = generateKingMoves(engine, player);

    auto addUniqueMoves = [&](const std::vector<Move>& moves) {
        for (const auto& move : moves) {
            std::string moveNotation = Utils::positionToUCI(move.from) + Utils::positionToUCI(move.to) + move.promotion;
            if (uniqueMoves.find(moveNotation) == uniqueMoves.end()) {
                uniqueMoves.insert(moveNotation);
                allMoves.push_back(move);
            }
        }
    };

    addUniqueMoves(pawnMoves);
    addUniqueMoves(knightMoves);
    addUniqueMoves(bishopMoves);
    addUniqueMoves(rookMoves);
    addUniqueMoves(queenMoves);
    addUniqueMoves(kingMoves);

    return allMoves;
}

std::vector<Move> MoveGenerator::generatePawnMoves(const ChessEngine& engine, int player) {
    std::vector<Move> moves;
    uint64_t pawns = player == 0 ? engine.whitePawns : engine.blackPawns;
    uint64_t ownPieces = player == 0 ? (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing)
                                     : (engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);
    uint64_t opponentPieces = player == 0 ? (engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing)
                                          : (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing);
    int enPassantTarget = engine.getEnPassantTarget();

    for (int square = 0; square < 64; ++square) {
        if (pawns & (1ULL << square)) {
            for (int direction : {8, 16, 7, 9}) {
                int targetSquare = square + (player == 0 ? direction : -direction);
                if (engine.isWithinBoard(targetSquare)) {
                    Move move(Utils::positionToUCI(square) + Utils::positionToUCI(targetSquare));
                    if (MoveValidator::isValidPawnMove(move, player, pawns, opponentPieces, enPassantTarget)) {
                        if ((player == 0 && targetSquare >= 56) || (player == 1 && targetSquare <= 7)) {
                            for (char promotion : {'q', 'r', 'b', 'n'}) {
                                Move promotionMove(Utils::positionToUCI(square) + Utils::positionToUCI(targetSquare) + promotion);
                                moves.push_back(promotionMove);
                            }
                        } else {
                            moves.push_back(move);
                        }
                    }
                }
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGenerator::generateKnightMoves(const ChessEngine& engine, int player) {
    std::vector<Move> moves;
    uint64_t knights = player == 0 ? engine.whiteKnights : engine.blackKnights;
    uint64_t ownPieces = player == 0 ? (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing)
                                     : (engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);

    for (int square = 0; square < 64; ++square) {
        if (knights & (1ULL << square)) {
            for (int offset : {6, 10, 15, 17, -6, -10, -15, -17}) {
                int targetSquare = square + offset;
                if (engine.isWithinBoard(targetSquare)) {
                    Move move(Utils::positionToUCI(square) + Utils::positionToUCI(targetSquare));
                    if (MoveValidator::isValidKnightMove(move, player, knights, ownPieces)) {
                        moves.push_back(move);
                    }
                }
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGenerator::generateBishopMoves(const ChessEngine& engine, int player) {
    std::vector<Move> moves;
    uint64_t bishops = player == 0 ? engine.whiteBishops : engine.blackBishops;
    uint64_t ownPieces = player == 0 ? (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing)
                                     : (engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);
    uint64_t occupied = (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing |
                         engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);

    for (int square = 0; square < 64; ++square) {
        if (bishops & (1ULL << square)) {
            for (int direction : {9, 7, -9, -7}) {
                int targetSquare = square + direction;
                while (engine.isWithinBoard(targetSquare) && abs((targetSquare % 8) - (square % 8)) == abs((targetSquare / 8) - (square / 8))) {
                    Move move(Utils::positionToUCI(square) + Utils::positionToUCI(targetSquare));
                    if (MoveValidator::isValidBishopMove(move, player, bishops, ownPieces, occupied)) {
                        moves.push_back(move);
                    }
                    if (occupied & (1ULL << targetSquare)) {
                        break;
                    }
                    targetSquare += direction;
                }
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGenerator::generateRookMoves(const ChessEngine& engine, int player) {
    std::vector<Move> moves;
    uint64_t rooks = player == 0 ? engine.whiteRooks : engine.blackRooks;
    uint64_t ownPieces = player == 0 ? (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing)
                                     : (engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);
    uint64_t occupied = (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing |
                         engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);

    for (int square = 0; square < 64; ++square) {
        if (rooks & (1ULL << square)) {
            for (int direction : {8, -8, 1, -1}) {
                for (int i = square + direction; i >= 0 && i < 64; i += direction) {
                    if (!engine.isWithinBoard(i)) break;
                    Move move(Utils::positionToUCI(square) + Utils::positionToUCI(i));
                    if (MoveValidator::isValidRookMove(move, player, rooks, ownPieces, occupied)) {
                        moves.push_back(move);
                    }
                    if (occupied & (1ULL << i)) {
                        break;
                    }
                }
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGenerator::generateQueenMoves(const ChessEngine& engine, int player) {
    std::vector<Move> moves;
    uint64_t queens = player == 0 ? engine.whiteQueens : engine.blackQueens;
    uint64_t ownPieces = player == 0 ? (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing)
                                     : (engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);
    uint64_t occupied = (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing |
                         engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);

    for (int square = 0; square < 64; ++square) {
        if (queens & (1ULL << square)) {
            // queen moves like both rooks and bishops
            for (int direction : {9, 7, -9, -7, 8, -8, 1, -1}) {
                for (int i = square + direction; i >= 0 && i < 64; i += direction) {
                    if (!engine.isWithinBoard(i)) break;
                    Move move(Utils::positionToUCI(square) + Utils::positionToUCI(i));
                    if (MoveValidator::isValidQueenMove(move, player, queens, ownPieces, occupied)) {
                        moves.push_back(move);
                    }
                    if (occupied & (1ULL << i)) {
                        break;
                    }
                }
            }
        }
    }

    return moves;
}

std::vector<Move> MoveGenerator::generateKingMoves(const ChessEngine& engine, int player) {
    std::vector<Move> moves;
    uint64_t king = player == 0 ? engine.whiteKing : engine.blackKing;
    uint64_t ownPieces = player == 0 ? (engine.whitePawns | engine.whiteKnights | engine.whiteBishops | engine.whiteRooks | engine.whiteQueens | engine.whiteKing)
                                     : (engine.blackPawns | engine.blackKnights | engine.blackBishops | engine.blackRooks | engine.blackQueens | engine.blackKing);

    for (int square = 0; square < 64; ++square) {
        if (king & (1ULL << square)) {
            for (int offset : {8, -8, 1, -1, 9, 7, -9, -7}) {
                int targetSquare = square + offset;
                if (engine.isWithinBoard(targetSquare)) {
                    Move move(Utils::positionToUCI(square) + Utils::positionToUCI(targetSquare));
                    if (MoveValidator::isValidKingMove(move, player, king, ownPieces)) {
                        moves.push_back(move);
                    }
                }
            }

            // castling
            if (MoveValidator::canCastleKingside(player, engine)) {
                Move kingsideCastle(Utils::positionToUCI(square) + Utils::positionToUCI(square + 2));
                moves.push_back(kingsideCastle);
            }
            if (MoveValidator::canCastleQueenside(player, engine)) {
                Move queensideCastle(Utils::positionToUCI(square) + Utils::positionToUCI(square - 2));
                moves.push_back(queensideCastle);
            }
        }
    }

    return moves;
}