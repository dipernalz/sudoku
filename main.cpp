#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "sudoku.h"
#include "sudoku_solver.h"

using namespace std;

int main() {
    auto start = chrono::system_clock::now();

    sudoku_solver solver;
    solver.set_puzzle("8__________36______7__9_2___5___7_______457_____1___3___1____68__85___1__9____4__");
    const sudoku& solution = solver.solve();
    solution.print_grid();

    cout << (chrono::system_clock::now() - start).count() / 1000000000.0 << "s" << endl;

    return 0;
}
