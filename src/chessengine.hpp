#ifndef CHESSENGINE_HPP
#define CHESSENGINE_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include "movegenerator.hpp"

enum class GameStatus {
    IN_PROGRESS,
    WHITE_CHECKMATED,
    BLACK_CHECKMATED,
    STALEMATE,
    INSUFFICIENT_MATERIAL,
    FIFTY_MOVE_DRAW,
    THREEFOLD_REPETITION,
    DRAW_AGREEMENT,
    BLACK_RESIGNS,
    WHITE_RESIGNS
};

enum class GameMode {
    HUMAN_VS_HUMAN,
    HUMAN_VS_AI,
    AI_VS_AI
};

enum class PlayerType {
    HUMAN,
    RANDOM_AI,
    GREEDY_AI
};

/**
 * @brief Overload of the << operator for GameStatus.
 *
 * @param os The output stream.
 * @param status The game status to output.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const GameStatus& status);


/**
 * @brief Struct to represent a move in the UCI format. E.g: "e2e4" (move 2 squares ahead with a pawn), "a7a8q" (pawn promotion to queen).
 */
struct Move {
    int from;
    int to;
    char promotion; // 'q', 'r', 'b', 'n' for pawn promotions

    
    /**
     * @brief Converts a position in algebraic notation to an integer.
     * @return int The integer representation of the position. 
    */
    int positionToInt(const std::string& pos) {
        if (pos.length() != 2) {
            throw std::invalid_argument("Invalid position length");
        }

        char file = pos[0];
        char rank = pos[1];

        if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
            throw std::invalid_argument("Invalid position format");
        }

        int fileIndex = file - 'a'; // 'a' -> 0, 'b' -> 1, ..., 'h' -> 7
        int rankIndex = rank - '1'; // '1' -> 0, '2' -> 1, ..., '8' -> 7

        return rankIndex * 8 + fileIndex; // 0-63
    }

    /** 
     * @brief Constructor for the Move struct.
     * @param notation The move in UCI notation.
    */
    Move(const std::string& notation) 
        : from(-1), to(-1), promotion('\0') {
        if (notation.length() == 4) { // regular move
            from = positionToInt(notation.substr(0, 2));
            to = positionToInt(notation.substr(2, 2));
        } else if (notation.length() == 5) { // pawn promotion
            from = positionToInt(notation.substr(0, 2));
            to = positionToInt(notation.substr(2, 2));
            promotion = notation[4];
        } else {
            throw std::invalid_argument("Invalid UCI move format");
        }
    }
};

class MoveValidator;
class MoveExecutor;

class ChessEngine {
public:
    /**
     * @brief Parses command line arguments.
     * @param argc The argument count.
     * @param argv The argument values.
     */    
    void parseArgs(int argc, char* argv[]);

    /**
     * @brief Constructor for the ChessEngine class.
     * Initializes the Zobrist table and starts a new game.
     */
    ChessEngine();

    /**
     * @brief Starts a new game by setting up the initial positions and clearing history.
     */
    void newGame();

    /**
     * @brief Makes a move on the board. Updates the board state and checks for game status.
     *
     * @param move The move to make.
     * @param player The player making the move.
     */
    void makeMove(const Move& move, int player);

    /**
     * @brief Makes a random valid move for the current player. 0 for white, 1 for black.
     *
     * @param player The player making the move.
     */
    void makeRandomMove(int player);

    /**
     * @brief Makes the best valid move based on evaluation of all valid moves for the current player.
     *
     * @param player The player making the move.
     */
    void makeGreedyMove(int player);
    
    /**
     * @brief Generates all possible moves for the given player.
     *
     * @return std::vector<Move> A vector of all possible moves.
     */
    std::vector<Move> generateAllPossibleMoves(int player) const;

    uint64_t whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens, whiteKing;
    uint64_t blackPawns, blackKnights, blackBishops, blackRooks, blackQueens, blackKing;

    /**
     * @brief Gets the status of the white king's movement.
     *
     * @return true If the white king has moved.
     * @return false Otherwise.
     */
    bool getWhiteKingMoved() const;

    /**
     * @brief Sets the status of the white king's movement.
     *
     * @param moved The new status.
     */
    void setWhiteKingMoved(bool moved);

    /**
     * @brief Gets the status of the white rook on A1's movement.
     *
     * @return true If the white rook on A1 has moved.
     * @return false Otherwise.
     */
    bool getWhiteRookA1Moved() const;

    /**
     * @brief Sets the status of the white rook on A1's movement.
     *
     * @param moved The new status.
     */
    void setWhiteRookA1Moved(bool moved);

    /**
     * @brief Gets the status of the white rook on H1's movement.
     *
     * @return true If the white rook on H1 has moved.
     * @return false Otherwise.
     */
    bool getWhiteRookH1Moved() const;

    /**
     * @brief Sets the status of the white rook on H1's movement.
     *
     * @param moved The new status.
     */
    void setWhiteRookH1Moved(bool moved);

    /**
     * @brief Gets the status of the black king's movement.
     *
     * @return true If the black king has moved.
     * @return false Otherwise.
     */
    bool getBlackKingMoved() const;

    /**
     * @brief Sets the status of the black king's movement.
     *
     * @param moved The new status.
     */
    void setBlackKingMoved(bool moved);

    /**
     * @brief Gets the status of the black rook on A8's movement.
     *
     * @return true If the black rook on A8 has moved.
     * @return false Otherwise.
     */
    bool getBlackRookA8Moved() const;

    /**
     * @brief Sets the status of the black rook on A8's movement.
     *
     * @param moved The new status.
     */    
    void setBlackRookA8Moved(bool moved);

    /**
     * @brief Gets the status of the black rook on H8's movement.
     *
     * @return true If the black rook on H8 has moved.
     * @return false Otherwise.
     */    
    bool getBlackRookH8Moved() const;

    /**
     * @brief Sets the status of the black rook on H8's movement.
     *
     * @param moved The new status.
     */    
    void setBlackRookH8Moved(bool moved);

    /**
     * @brief Gets the en passant target square.
     *
     * @return int The en passant target square.
     */    
    int getEnPassantTarget() const;

    /**
     * @brief Sets the en passant target square.
     *
     * @param target The new en passant target square.
     */
    void setEnPassantTarget(int target);

    /**
     * @brief Gets the current game status.
     *
     * @return GameStatus The current game status.
     */    
    GameStatus getGameStatus() const;

    /**
     * @brief Starts a game with the specified mode. Includes main game loop. Prints the board after each move.
     *
     * @param mode The game mode to start.
     */    
    void startGame(GameMode mode);

    /**
     * @brief Makes a move for the current player. If the player is human, prompts for a move. If the player is AI, makes a random move or a greedy move.
     *
     * @param player The player making the move.
     */    
    void playerMove(int player);

    /**
     * @brief Checks if the game is a draw by repetition.
     *
     * @return true If the same position has occurred three times.
     * @return false Otherwise.
     */        
    bool isRepetitionDraw() const;

    /**
     * @brief Checks if the game is a draw by the fifty-move rule.
     *
     * @return true If the half-move clock is greater than or equal to 100.
     * @return false Otherwise.
     */    
    bool isFiftyMoveDraw() const;

    /**
     * @brief Handles a human player's move.
     *
     * @param player The player making the move.
     */    
    void makeHumanMove(int player);

    // function to save game state to a file 
    void saveGame(const std::string& path) const;

    // handling the game save during a game
    void handleGameSave(int player);

    /**
     * @brief Saves the game state to a file.
     *
     * @param path The path to the file.
     * @return int The current player.
     */
    void saveGameToFile(const std::string& path, int currentPlayer) const;

    /**
     * @brief Loads the game state from a file.
     *
     * @param path The path to the file.
     * @param isEval Whether the game is being loaded for evaluation, if so game loop is skipped.
     * @return int The current player.
     */
    void loadGameFromFile(const std::string& path, bool isEval);    

private:
    /**
     * @brief Checks if a square is within the board.
     *
     * @param square The square to check.
     * @return true If the square is within the board.
     * @return false Otherwise.
     */
    bool isWithinBoard(int square) const;

    /**
     * @brief Handles player resignation.
     *
     * @param player The player who resigns.
     */    
    void handleResignation(int player);

    /**
     * @brief Prompts the player for a move.
     *
     * @param player The player to prompt.
     * @return std::string The move entered by the player.
     */    
    std::string askForMove(int player);

    /**
     * @brief Handles draw agreement between players.
     *
     * @param player The player offering the draw.
     * @return true If the draw is agreed upon.
     * @return false Otherwise.
     */    
    bool handleDrawAgreement(int player);
    
    /**
     * @brief Updates the game status based on the current board state after a move is made.
     *
     * @param player The player currently making a move.
     */
    void updateGameStatus(int player);

    /**
     * @brief Calculates the Zobrist hash for the current position.
     *
     * @return uint64_t The Zobrist hash.
     */    
    uint64_t calculateZobristHash() const;

    /**
     * @brief Initializes the Zobrist table for hashing.
     */
    void initializeZobristTable();

    // castling flags
    bool whiteKingMoved, whiteRookA1Moved, whiteRookH1Moved;
    bool blackKingMoved, blackRookA8Moved, blackRookH8Moved;

    PlayerType whitePlayerType;
    PlayerType blackPlayerType;

    // en passant target square (-1 if not applicable)
    int enPassantTarget;

    GameStatus status;

    // history of board positions
    std::unordered_map<uint64_t, int> positionHistory;
    std::vector<uint64_t> positionList;

    uint64_t zobristTable[12][64]; // 6 pieces for each color on 64 squares
    uint64_t zobristCastle[4];     // 4 castling rights (white king, white queen, black king, black queen)
    uint64_t zobristEnPassant[8];  // 8 possible en passant files
    uint64_t zobristSide;          // side to move
    int halfMoveClock;    

    friend class MoveValidator;
    friend class MoveExecutor;
    friend class MoveGenerator;
};

#endif // CHESSENGINE_HPP