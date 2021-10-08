#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "sudoku.h"
#include "sudoku_solver.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Please provide a sudoku puzzle as an argument" << endl;
        return 0;
    }

    auto start_time = chrono::system_clock::now();

    sudoku puzzle(argv[1]);
    cout << endl
         << "Initial Puzzle:" << endl;
    puzzle.print_grid();
    cout << endl;

    sudoku_solver solver;
    solver.set_puzzle(argv[1]);
    const sudoku& solution = solver.solve();

    cout << "Solution:" << endl;
    solution.print_grid();
    cout << endl;

    auto end_time = chrono::system_clock::now();
    auto time_elapsed = chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    cout << "Time elapsed: " << time_elapsed << "ms" << endl;

    return 0;
}
