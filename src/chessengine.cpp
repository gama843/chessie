#include "chessengine.hpp"
#include "movevalidator.hpp"
#include "moveexecutor.hpp"
#include "utils.hpp"
#include <iostream>
#include <bitset>
#include <ctime>
#include <climits>
#include <random>
#include <fstream>
#include <chrono>

void ChessEngine::saveGameToFile(const std::string& path, int currentPlayer) const {
    std::ofstream file(path);
    if (file.is_open()) {
        // save board state
        file << whitePawns << ' ' << whiteKnights << ' ' << whiteBishops << ' ' << whiteRooks << ' '
             << whiteQueens << ' ' << whiteKing << '\n';
        file << blackPawns << ' ' << blackKnights << ' ' << blackBishops << ' ' << blackRooks << ' '
             << blackQueens << ' ' << blackKing << '\n';

        // save castling flags
        file << whiteKingMoved << ' ' << whiteRookA1Moved << ' ' << whiteRookH1Moved << ' '
             << blackKingMoved << ' ' << blackRookA8Moved << ' ' << blackRookH8Moved << '\n';

        // save en passant target
        file << enPassantTarget << '\n';

        // save half-move clock
        file << halfMoveClock << '\n';

        // save position history
        file << positionList.size() << '\n';
        for (const auto& hash : positionList) {
            file << hash << ' ';
        }
        file << '\n';

        // save the current player
        file << currentPlayer << '\n';

        // save the player types
        file << static_cast<int>(whitePlayerType) << ' ' << static_cast<int>(blackPlayerType) << '\n';

        // save the Zobrist table
        for (int piece = 0; piece < 12; ++piece) {
            for (int square = 0; square < 64; ++square) {
                file << zobristTable[piece][square] << ' ';
            }
            file << '\n';
        }
        for (int i = 0; i < 4; ++i) {
            file << zobristCastle[i] << ' ';
        }
        file << '\n';
        for (int i = 0; i < 8; ++i) {
            file << zobristEnPassant[i] << ' ';
        }
        file << '\n';
        file << zobristSide << '\n';

        // save the current game status
        file << static_cast<int>(status) << '\n';

        file.close();
    }
}

// loads the game state from a file and returns the current player
void ChessEngine::loadGameFromFile(const std::string& path, bool isEval) {
    std::ifstream file(path);
    if (file.is_open()) {
        // load board state
        int player; 

        file >> whitePawns >> whiteKnights >> whiteBishops >> whiteRooks >> whiteQueens >> whiteKing;
        file >> blackPawns >> blackKnights >> blackBishops >> blackRooks >> blackQueens >> blackKing;

        // load castling flags
        file >> whiteKingMoved >> whiteRookA1Moved >> whiteRookH1Moved;
        file >> blackKingMoved >> blackRookA8Moved >> blackRookH8Moved;

        // load en passant target
        file >> enPassantTarget;

        // load half-move clock
        file >> halfMoveClock;

        // load position history
        size_t positionListSize;
        file >> positionListSize;
        positionHistory.clear();
        positionList.clear();
        for (size_t i = 0; i < positionListSize; ++i) {
            uint64_t hash;
            file >> hash;
            positionList.push_back(hash);
            positionHistory[hash]++;
        }

        // load the current player
        file >> player;

        // load the player types
        int whitePlayerTypeInt, blackPlayerTypeInt;
        file >> whitePlayerTypeInt >> blackPlayerTypeInt;
        whitePlayerType = static_cast<PlayerType>(whitePlayerTypeInt);
        blackPlayerType = static_cast<PlayerType>(blackPlayerTypeInt);

        // load the Zobrist table
        for (int piece = 0; piece < 12; ++piece) {
            for (int square = 0; square < 64; ++square) {
                file >> zobristTable[piece][square];
            }
        }
        for (int i = 0; i < 4; ++i) {
            file >> zobristCastle[i];
        }
        for (int i = 0; i < 8; ++i) {
            file >> zobristEnPassant[i];
        }
        file >> zobristSide;

        // load the current game status
        int statusInt;
        file >> statusInt;
        status = static_cast<GameStatus>(statusInt);

        file.close();

        std::cout << "Game has been loaded from file." << std::endl;
        Utils::printBoard(*this);
        
        if (!isEval) {
            while (status == GameStatus::IN_PROGRESS) {
                playerMove(player);
                status = getGameStatus();
                std::cout << "Game status: " << status << std::endl;
                player = 1 - player;
                Utils::printBoard(*this);
            }
        }
    }
    else {
        std::cerr << "Unable to open file." << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const GameStatus& status) {
    switch (status) {
        case GameStatus::IN_PROGRESS:
            os << "Game in progress";
            break;
        case GameStatus::WHITE_CHECKMATED:
            os << "White is checkmated";
            break;
        case GameStatus::BLACK_CHECKMATED:
            os << "Black is checkmated";
            break;
        case GameStatus::STALEMATE:
            os << "Stalemate";
            break;
        case GameStatus::INSUFFICIENT_MATERIAL:
            os << "Insufficient material";
            break;
        case GameStatus::FIFTY_MOVE_DRAW:
            os << "Fifty move draw";
            break;
        case GameStatus::THREEFOLD_REPETITION:
            os << "Threefold repetition";
            break;
        case GameStatus::DRAW_AGREEMENT:
            os << "Draw agreement";
            break;
        case GameStatus::BLACK_RESIGNS:
            os << "Black resigns. White wins.";
            break;
        case GameStatus::WHITE_RESIGNS:
            os << "White resigns. Black wins.";
            break;
        default:
            os << "Unknown status";
            break;
    }
    return os;
}

ChessEngine::ChessEngine() {
    initializeZobristTable();
    newGame();
    std::srand(std::time(nullptr)); // seed
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

    enPassantTarget = -1;

    status = GameStatus::IN_PROGRESS;

    // clear the position history
    positionHistory.clear();
    positionList.clear();

    // hash for the initial position
    uint64_t hash = calculateZobristHash();
    positionHistory[hash] = 1;
    positionList.push_back(hash);

    halfMoveClock = 0;
}

void ChessEngine::initializeZobristTable() {
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    // Zobrist table init for pieces
    for (int piece = 0; piece < 12; ++piece) {
        for (int square = 0; square < 64; ++square) {
            zobristTable[piece][square] = rng();
        }
    }

    // Zobrist table init for castling rights
    for (int i = 0; i < 4; ++i) {
        zobristCastle[i] = rng();
    }

    // Zobrist table init for en passant targets
    for (int i = 0; i < 8; ++i) {
        zobristEnPassant[i] = rng();
    }

    // Zobrist table init for the side to move
    zobristSide = rng();
}

uint64_t ChessEngine::calculateZobristHash() const {
    uint64_t hash = 0;

    // pieces
    for (int square = 0; square < 64; ++square) {
        if (whitePawns & (1ULL << square)) hash ^= zobristTable[0][square];
        if (whiteKnights & (1ULL << square)) hash ^= zobristTable[1][square];
        if (whiteBishops & (1ULL << square)) hash ^= zobristTable[2][square];
        if (whiteRooks & (1ULL << square)) hash ^= zobristTable[3][square];
        if (whiteQueens & (1ULL << square)) hash ^= zobristTable[4][square];
        if (whiteKing & (1ULL << square)) hash ^= zobristTable[5][square];

        if (blackPawns & (1ULL << square)) hash ^= zobristTable[6][square];
        if (blackKnights & (1ULL << square)) hash ^= zobristTable[7][square];
        if (blackBishops & (1ULL << square)) hash ^= zobristTable[8][square];
        if (blackRooks & (1ULL << square)) hash ^= zobristTable[9][square];
        if (blackQueens & (1ULL << square)) hash ^= zobristTable[10][square];
        if (blackKing & (1ULL << square)) hash ^= zobristTable[11][square];
    }

    // castling rights
    if (!whiteKingMoved) {
        if (!whiteRookA1Moved) hash ^= zobristCastle[0];
        if (!whiteRookH1Moved) hash ^= zobristCastle[1];
    }
    if (!blackKingMoved) {
        if (!blackRookA8Moved) hash ^= zobristCastle[2];
        if (!blackRookH8Moved) hash ^= zobristCastle[3];
    }

    // en passant target
    if (enPassantTarget != -1) {
        hash ^= zobristEnPassant[enPassantTarget % 8];
    }

    // side to move
    hash ^= zobristSide;

    return hash;
}

bool ChessEngine::isRepetitionDraw() const {
    for (const auto& entry : positionHistory) {
        if (entry.second >= 3) {
            return true;
        }
    }
    return false;
}

void ChessEngine::startGame(GameMode mode) {
    newGame();

    switch (mode) {
        case GameMode::HUMAN_VS_HUMAN:
            whitePlayerType = PlayerType::HUMAN;
            blackPlayerType = PlayerType::HUMAN;
            break;
        case GameMode::HUMAN_VS_AI:
            whitePlayerType = PlayerType::HUMAN;
            blackPlayerType = PlayerType::GREEDY_AI; // or RANDOM_AI
            break;
        case GameMode::AI_VS_AI:
            whitePlayerType = PlayerType::GREEDY_AI; // or RANDOM_AI
            blackPlayerType = PlayerType::RANDOM_AI; // or GREEDY_AI
            break;
    }

    int player = 0;
    Utils::printBoard(*this);

    while (status == GameStatus::IN_PROGRESS) {
        playerMove(player);
        status = getGameStatus();
        std::cout << "Game status: " << status << std::endl;
        player = 1 - player;
        Utils::printBoard(*this);
    }    
}

void ChessEngine::handleResignation(int player) {
    if (player == 0) {
        status = GameStatus::WHITE_RESIGNS;
    } else {
        status = GameStatus::BLACK_RESIGNS;
    }
}

std::string ChessEngine::askForMove(int player) {
    std::string moveStr;
    if (player == 0) {
        std::cout << "Enter move for White in UCI format: ";
    } else {
        std::cout << "Enter move for Black in UCI format: ";
    }
    std::cin >> moveStr;
    return moveStr;
}

bool ChessEngine::handleDrawAgreement(int player) {
    // check if the other player agrees to a draw
    if (player == 0) {
        // if other player is human, ask for draw agreement
        if (blackPlayerType == PlayerType::HUMAN) {
            std::cout << "White offers a draw. Does Black accept? (yes/no): ";
        } else {
            // if other player is AI, reject the draw offer
            std::cout << "Draw offer declined." << std::endl;
            return false;
        }
    } else {
        // if other player is human, ask for draw agreement
        if (whitePlayerType == PlayerType::HUMAN) {
            std::cout << "Black offers a draw. Does White accept? (yes/no): ";
        } else {
            // if other player is AI, reject the draw offer
            std::cout << "Draw offer declined." << std::endl;
            return false;
        }
    }

    std::string response;
    std::cin >> response;
    if (response == "yes") {
        status = GameStatus::DRAW_AGREEMENT;
        return true;
    }

    // if the other player does not agree to a draw, continue the game
    std::cout << "Draw offer declined." << std::endl;
    return false;
}

void ChessEngine::handleGameSave(int player) {
    std::string path;
    std::cout << "Enter a filename to save the game: ";
    std::cin >> path;
    saveGameToFile(path, player);
    std::cout << "Game saved to file: " << path << std::endl;
}

void ChessEngine::makeHumanMove(int player) {
    std::string moveStr = askForMove(player);

    if (moveStr == "draw") {
        if (!handleDrawAgreement(player)) {
            makeHumanMove(player);
        }
    }

    else if (moveStr == "resign") {
        handleResignation(player);
    }

    else if (moveStr == "save") {
        handleGameSave(player);
        makeHumanMove(player);
    }

    else if (moveStr == "exit") {
        exit(0);
    }

    else {
        try {
            Move move(moveStr);
            if (MoveValidator::isValidMove(move, player, *this)) {
                makeMove(move, player);
            } else {
                std::cout << "Invalid move. Try again." << std::endl;
                makeHumanMove(player);
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid move format. Try again." << std::endl;
            makeHumanMove(player);
        }
    }
}

void ChessEngine::playerMove(int player) {
    if ((player == 0 && whitePlayerType == PlayerType::HUMAN) || (player == 1 && blackPlayerType == PlayerType::HUMAN)) {
        makeHumanMove(player);
    } else if ((player == 0 && whitePlayerType == PlayerType::RANDOM_AI) || (player == 1 && blackPlayerType == PlayerType::RANDOM_AI)) {
        makeRandomMove(player);
    } else {
        makeGreedyMove(player);
    }
}

void ChessEngine::makeRandomMove(int player) {
    std::vector<Move> validMoves = MoveGenerator::generateAllValidMoves(*this, player);
    if (validMoves.empty()) {
        throw std::runtime_error("No valid moves available.");
    }
    int randomIndex = std::rand() % validMoves.size();
    Move randomMove = validMoves[randomIndex];
    makeMove(randomMove, player);
}

void ChessEngine::makeGreedyMove(int player) {
    std::vector<Move> validMoves = MoveGenerator::generateAllValidMoves(*this, player);
    if (validMoves.empty()) {
        throw std::runtime_error("No valid moves available.");
    }

    int bestScore = (player == 0) ? INT_MIN : INT_MAX;

    // first, find the best score, then create a list of moves with the best score, then choose a random move from that list
    for (const Move& move : validMoves) {
        ChessEngine hypotheticalEngine = *this;
        MoveExecutor::makeMove(hypotheticalEngine, move, player);
        int score = Utils::evaluateBoard(hypotheticalEngine, player);

        if ((player == 0 && score > bestScore) || (player == 1 && score < bestScore)) {
            bestScore = score;
        }
    }

    std::vector<Move> bestMoves;
    for (const Move& move : validMoves) {
        ChessEngine hypotheticalEngine = *this;
        MoveExecutor::makeMove(hypotheticalEngine, move, player);
        int score = Utils::evaluateBoard(hypotheticalEngine, player);

        if (score == bestScore) {
            bestMoves.push_back(move);
        }
    }

    int randomIndex = std::rand() % bestMoves.size();
    Move bestMove = bestMoves[randomIndex];

    makeMove(bestMove, player);
}

void ChessEngine::makeMove(const Move& move, int player) {
    if (status != GameStatus::IN_PROGRESS) {
        std::cout << "Game over. No more moves allowed." << std::endl;
        return;
    }    

    if (player == 0) {
        std::cout << "Making move: " << Utils::positionToUCI(move.from) + Utils::positionToUCI(move.to) << " Player: white" <<  std::endl;
    } else {
        std::cout << "Making move: " << Utils::positionToUCI(move.from) + Utils::positionToUCI(move.to) << " Player: black" <<  std::endl;
    }
    MoveExecutor::makeMove(*this, move, player);
    
    // if the move was a double pawn move, set the en passant target
    if (player == 0 && (move.to == move.from + 16)) { // white double pawn move
        enPassantTarget = move.from + 8;
    } else if (player == 1 && (move.to == move.from - 16)) { // black double pawn move
        enPassantTarget = move.from - 8;
    } else {
        enPassantTarget = -1;
    }

    bool isPawnMove = ((whitePawns | blackPawns) & (1ULL << move.from)) != 0;
    bool isCapture = ((whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing |
                       blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing) & (1ULL << move.to)) != 0;

    if (isPawnMove || isCapture) {
        halfMoveClock = 0;
    } else {
        halfMoveClock++;
    }

    // update position history
    uint64_t hash = calculateZobristHash();
    positionHistory[hash]++;
    positionList.push_back(hash);

    updateGameStatus(player);
}

bool ChessEngine::isFiftyMoveDraw() const {
    return halfMoveClock >= 100;
}

void ChessEngine::updateGameStatus(int player) {
    if (status == GameStatus::BLACK_RESIGNS || status == GameStatus::WHITE_RESIGNS) {
        return;
    }
    std::string gameStatus = Utils::getGameStatus(*this, player);
    if (gameStatus == "White is checkmated") {
        status = GameStatus::WHITE_CHECKMATED;
    } else if (gameStatus == "Black is checkmated") {
        status = GameStatus::BLACK_CHECKMATED;
    } else if (gameStatus == "Stalemate") {
        status = GameStatus::STALEMATE;
    } else if (gameStatus == "Insufficient material") {
        status = GameStatus::INSUFFICIENT_MATERIAL;
    } else if (gameStatus == "Fifty move draw") {
        status = GameStatus::FIFTY_MOVE_DRAW;
    } else if (gameStatus == "Threefold repetition") {
        status = GameStatus::THREEFOLD_REPETITION;
    } else if (gameStatus == "Draw agreement") {
        status = GameStatus::DRAW_AGREEMENT;
    } else {
        status = GameStatus::IN_PROGRESS;
    }
}

GameStatus ChessEngine::getGameStatus() const {
    return status;
}

bool ChessEngine::isWithinBoard(int square) const {
    return square >= 0 && square < 64;
}

std::vector<Move> ChessEngine::generateAllPossibleMoves(int player) const {
    return MoveGenerator::generateAllMoves(*this, player);
}

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
int ChessEngine::getEnPassantTarget() const { return enPassantTarget; }
void ChessEngine::setEnPassantTarget(int target) { enPassantTarget = target; }

void ChessEngine::parseArgs(int argc, char* argv[]) {
    GameMode mode = GameMode::HUMAN_VS_HUMAN; // default mode

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--help" || arg == "-h") {
            Utils::printHelp();
            exit(0);
        } else if (arg == "--new" || arg == "-n") {
            newGame();
            std::cout << "New game started. Here is the initial board:" << std::endl;
            startGame(mode);
        } else if (arg == "--file" || arg == "-f") {
            if (i + 1 < argc) {
                std::string path = argv[++i];
                loadGameFromFile(path, false);
            } else {
                std::cerr << "No file path provided after --file" << std::endl;
                Utils::printHelp();
                exit(1);
            }
        } else if (arg == "--eval" || arg == "-e") {
            if (i + 1 < argc) {
                std::string path = argv[++i];
                // load the game state from the file
                loadGameFromFile(path, true);
                // eval for white 
                std::cout << "Evaluation for the white player: " << Utils::evaluateBoard(*this, 0) << std::endl;                    
                // eval for black
                std::cout << "Evaluation for the black player: " << Utils::evaluateBoard(*this, 1) << std::endl;
            } else {
                std::cerr << "No file path provided after --help" << std::endl;
                Utils::printHelp();
                exit(1);
            }
        } else if (arg == "--mode") {
            if (i + 1 < argc) {
                std::string modeStr = argv[++i];
                if (modeStr == "hvh") {
                    mode = GameMode::HUMAN_VS_HUMAN;
                } else if (modeStr == "hva") {
                    mode = GameMode::HUMAN_VS_AI;
                } else if (modeStr == "ava") {
                    mode = GameMode::AI_VS_AI;
                } else {
                    std::cerr << "Invalid mode: " << modeStr << std::endl;
                    Utils::printHelp();
                    exit(1);
                }
                startGame(mode);
            } else {
                std::cerr << "No mode provided after --mode" << std::endl;
                Utils::printHelp();
                exit(1);
            }
        }
    }
}