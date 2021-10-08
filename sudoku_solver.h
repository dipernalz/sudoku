#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <string>
#include <unordered_set>
#include <vector>

#include "sudoku.h"

class sudoku_solver {
   private:
    sudoku puzzle;
    const sudoku empty_puzzle;

    void generate_constraints();

    void generate_neighbors();

    void generate_symbols();

    const sudoku solve_sudoku(const sudoku& puzzle);

   public:
    enum { N = 9 };
    enum { WIDTH = 3 };
    enum { HEIGHT = 3 };

    sudoku_solver();

    static std::vector<std::unordered_set<int>>& get_constraints() {
        static std::vector<std::unordered_set<int>> constraints;
        return constraints;
    }

    static std::vector<std::unordered_set<int>>& get_neighbors() {
        static std::vector<std::unordered_set<int>> neighbors;
        return neighbors;
    }

    static std::unordered_set<char>& get_symbols() {
        static std::unordered_set<char> symbols;
        return symbols;
    }

    void set_puzzle(const std::string& puzzle);

    void set_puzzle(sudoku& sudoku);

    sudoku solve();
};

#endif
