#include <gtest/gtest.h>
#include "chessengine.hpp"
#include "utils.hpp"
#include <chrono>
#include <fstream>

void logPerformanceResults(const std::string& test_name, const std::string& result) {
    std::ofstream log_file;
    log_file.open("performance_tests.log", std::ios_base::app); // open in append mode
    if (log_file.is_open()) {
        log_file << test_name << ": " << result << std::endl;
        log_file.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
}

TEST(PerformanceTest, EvaluateBoardSpeed) {
    ChessEngine engine;
    engine.newGame();

    int player = 0;
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 1000; ++i) {
        Utils::evaluateBoard(engine, player);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::string result = "Evaluation speed: " + std::to_string(duration) + " ms for 1000 evaluations.";
    
    logPerformanceResults("EvaluateBoardSpeed", result);
}

TEST(PerformanceTest, GenerateMovesSpeed) {
    ChessEngine engine;
    engine.newGame();

    int player = 0;
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 1000; ++i) {
        engine.generateAllPossibleMoves(player);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::string result = "Move generation speed: " + std::to_string(duration) + " ms for 1000 move generations.";
    
    logPerformanceResults("GenerateMovesSpeed", result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}