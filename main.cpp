#include <chrono>
#include <iomanip>
#include <iostream>

#include "sudoku.hpp"
#include "sudoku_constants.hpp"
#include "sudoku_solver.hpp"

using uint128_t = __uint128_t;

int main(int argc, char* argv[]) {
    generate_bitmasks();

    uint128_t constraints[N * WIDTH] = {0};
    generate_constraints(constraints);

    uint128_t neighbors[N * N] = {0};
    generate_neighbors(neighbors, constraints);

    unsigned char index_to_symbol[N] = {0};
    uint8_t symbol_to_index[128] = {0};
    generate_symbols(index_to_symbol, symbol_to_index);

    if (argc == 1) {
        std::cout << "Please provide a sudoku puzzle as an argument" << std::endl;
        return 0;
    }

    auto start_time = std::chrono::system_clock::now();

    sudoku puzzle(argv[1], index_to_symbol, neighbors, symbol_to_index);
    std::cout << std::endl;
    std::cout << "Puzzle:" << std::endl;
    puzzle.print_grid();

    if (!check_puzzle(puzzle, constraints)) {
        std::cout << "Invalid puzzle" << std::endl;
        std::cout << std::endl;
        return 0;
    }
    sudoku solution = solve_puzzle(puzzle);

    std::cout << "Solution:" << std::endl;
    if (!solution.is_valid()) {
        std::cout << "No solution found" << std::endl;
        std::cout << std::endl;
    } else {
        solution.print_grid();
    }

    auto end_time = std::chrono::system_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Time elapsed: " << time_elapsed << "s" << std::endl;
    std::cout << std::endl;

    return 0;
}
