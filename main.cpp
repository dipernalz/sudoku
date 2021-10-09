#include <chrono>
#include <iomanip>
#include <iostream>

#include "sudoku.h"
#include "sudoku_solver.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Please provide a sudoku puzzle as an argument" << std::endl;
        return 0;
    }

    auto start_time = std::chrono::system_clock::now();

    sudoku_solver solver;
    sudoku puzzle(argv[1]);
    std::cout << std::endl;
    std::cout << "Puzzle:" << std::endl;
    puzzle.print_grid();
    std::cout << std::endl;

    solver.set_puzzle(puzzle);
    if (!solver.check_puzzle()) {
        std::cout << "Invalid puzzle" << std::endl;
        std::cout << std::endl;
        return 0;
    }
    sudoku solution = solver.get_solution();

    std::cout << "Solution:" << std::endl;
    if (!solution.is_valid()) {
        std::cout << "No solution found" << std::endl;
        std::cout << std::endl;
    } else {
        solution.print_grid();
        std::cout << std::endl;
    }

    auto end_time = std::chrono::system_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Time elapsed: " << time_elapsed << "s" << std::endl;
    std::cout << std::endl;

    return 0;
}
