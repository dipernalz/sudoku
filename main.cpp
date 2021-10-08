#include <iostream>
#include <unordered_set>
#include <vector>

#include "Sudoku.h"

using namespace std;

int main() {
    SudokuSolver solver("8__________36______7__9_2___5___7_______457_____1___3___1____68__85___1__9____4__");
    Sudoku solution = solver.solve();
    solution.print();

    return 0;
}
