#include <iostream>
#include <unordered_set>
#include <vector>

#include "Sudoku.h"

using namespace std;

int main() {
    SudokuSolver solver("29_46_15784172__39___13_8__6____1______2___96_89___2_5___9__5__93_8_7____16__2_7_");
    Sudoku solution = solver.solve();
    solution.print();

    return 0;
}
