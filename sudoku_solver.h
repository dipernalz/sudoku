#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <string>
#include <unordered_set>
#include <vector>

#include "sudoku.h"

using u_char_set = std::unordered_set<char>;
using u_int_set = std::unordered_set<int>;

class sudoku_solver {
   private:
    sudoku puzzle;

    void generate_constraints() const;

    void generate_neighbors() const;

    void generate_symbols() const;

    sudoku solve_sudoku(sudoku puzzle) const;

   public:
    enum { N = 9,
           WIDTH = 3,
           HEIGHT = 3 };

    sudoku_solver();

    static std::vector<u_int_set>& get_constraints() {
        static std::vector<u_int_set> constraints;
        return constraints;
    }

    static std::vector<u_int_set>& get_neighbors() {
        static std::vector<u_int_set> neighbors;
        return neighbors;
    }

    static u_char_set& get_symbols() {
        static u_char_set symbols;
        return symbols;
    }

    const sudoku& get_puzzle() const;

    sudoku get_solution() const;

    void set_puzzle(const std::string& puzzle);

    void set_puzzle(const sudoku& sudoku);

    bool check_puzzle() const;
};

#endif
