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

    sudoku puzzle(argv[1]);
    std::cout << std::endl
              << "Initial Puzzle:" << std::endl;
    puzzle.print_grid();
    std::cout << std::endl;

    sudoku_solver solver;
    solver.set_puzzle(argv[1]);
    const sudoku& solution = solver.solve();

    std::cout << "Solution:" << std::endl;
    solution.print_grid();
    std::cout << std::endl;

    auto end_time = std::chrono::system_clock::now();
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>
                            (end_time - start_time).count() / 1000.0;
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Time elapsed: " << time_elapsed << "s" << std::endl;

    return 0;
}
