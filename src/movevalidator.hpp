#ifndef MOVEVALIDATOR_HPP
#define MOVEVALIDATOR_HPP

#include <cstdint>
#include "chessengine.hpp"

/**
 * @class MoveValidator
 * @brief Validates the legality of chess moves.
 */
class MoveValidator {
public:
    /**
     * @brief Checks if a move is valid for the given player.
     * @param move The move to validate.
     * @param player The player making the move (0 for white, 1 for black).
     * @param engine The chess engine containing the game state.
     * @return True if the move is valid, false otherwise.
     */
    static bool isValidMove(const Move& move, int player, const ChessEngine& engine);

    /**
     * @brief Checks if a pawn move is valid for the given player.
     * @param move The pawn move to validate.
     * @param player The player making the move (0 for white, 1 for black).
     * @param pawns The bitboard representing the player's pawns.
     * @param opponentPieces The bitboard representing the opponent's pieces.
     * @param enPassantTarget The en passant target square.
     * @return True if the pawn move is valid, false otherwise.
     */
    static bool isValidPawnMove(const Move& move, int player, uint64_t pawns, uint64_t opponentPieces, int enPassantTarget);

    /**
     * @brief Checks if a knight move is valid for the given player.
     * @param move The knight move to validate.
     * @param player The player making the move (0 for white, 1 for black).
     * @param knights The bitboard representing the player's knights.
     * @param ownPieces The bitboard representing the player's own pieces.
     * @return True if the knight move is valid, false otherwise.
     */
    static bool isValidKnightMove(const Move& move, int player, uint64_t knights, uint64_t ownPieces);

    /**
     * @brief Checks if a bishop move is valid for the given player.
     * @param move The bishop move to validate.
     * @param player The player making the move (0 for white, 1 for black).
     * @param bishops The bitboard representing the player's bishops.
     * @param ownPieces The bitboard representing the player's own pieces.
     * @param occupied The bitboard representing all occupied squares.
     * @return True if the bishop move is valid, false otherwise.
     */
    static bool isValidBishopMove(const Move& move, int player, uint64_t bishops, uint64_t ownPieces, uint64_t occupied);

    /**
     * @brief Checks if a rook move is valid for the given player.
     * @param move The rook move to validate.
     * @param player The player making the move (0 for white, 1 for black).
     * @param rooks The bitboard representing the player's rooks.
     * @param ownPieces The bitboard representing the player's own pieces.
     * @param occupied The bitboard representing all occupied squares.
     * @return True if the rook move is valid, false otherwise.
     */
    static bool isValidRookMove(const Move& move, int player, uint64_t rooks, uint64_t ownPieces, uint64_t occupied);

    /**
     * @brief Checks if a queen move is valid for the given player.
     * @param move The queen move to validate.
     * @param player The player making the move (0 for white, 1 for black).
     * @param queens The bitboard representing the player's queens.
     * @param ownPieces The bitboard representing the player's own pieces.
     * @param occupied The bitboard representing all occupied squares.
     * @return True if the queen move is valid, false otherwise.
     */
    static bool isValidQueenMove(const Move& move, int player, uint64_t queens, uint64_t ownPieces, uint64_t occupied);

    /**
     * @brief Checks if a king move is valid for the given player.
     * @param move The king move to validate.
     * @param player The player making the move (0 for white, 1 for black).
     * @param king The bitboard representing the player's king.
     * @param ownPieces The bitboard representing the player's own pieces.
     * @return True if the king move is valid, false otherwise.
     */
    static bool isValidKingMove(const Move& move, int player, uint64_t king, uint64_t ownPieces);

    /**
     * @brief Checks if the player can castle kingside.
     * @param player The player to check for (0 for white, 1 for black).
     * @param engine The chess engine containing the game state.
     * @return True if the player can castle kingside, false otherwise.
     */
    static bool canCastleKingside(int player, const ChessEngine& engine);

    /**
     * @brief Checks if the player can castle queenside.
     * @param player The player to check for (0 for white, 1 for black).
     * @param engine The chess engine containing the game state.
     * @return True if the player can castle queenside, false otherwise.
     */
    static bool canCastleQueenside(int player, const ChessEngine& engine);

    /**
     * @brief Checks if a move exposes the player's king to check.
     * @param move The move to validate.
     * @param player The player making the move (0 for white, 1 for black).
     * @param engine The chess engine containing the game state.
     * @return True if the move exposes the king to check, false otherwise.
     */
    static bool doesMoveExposeKing(const Move& move, int player, const ChessEngine& engine);

    /**
     * @brief Checks if a square is attacked by the specified player.
     * @param engine The chess engine containing the game state.
     * @param square The square to check.
     * @param attacker The player attacking the square (0 for white, 1 for black).
     * @return True if the square is attacked, false otherwise.
     */
    static bool isSquareAttacked(const ChessEngine& engine, int square, int attacker);
};

#endif // MOVEVALIDATOR_HPP