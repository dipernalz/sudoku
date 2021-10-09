#include "sudoku_solver.h"

#include <iostream>
#include <string>
#include <unordered_set>

#include "sudoku.h"

/* private */
void sudoku_solver::generate_constraints() const {
    for (int i = 0; i < N; i++) {
        u_int_set column_set;
        for (int j = i; j < N * N; j += N) {
            column_set.insert(j);
        }
        sudoku_solver::get_constraints().push_back(column_set);
    }
    for (int i = 0; i < N * N; i += N) {
        u_int_set row_set;
        for (int j = i; j < i + N; j++) {
            row_set.insert(j);
        }
        sudoku_solver::get_constraints().push_back(row_set);
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            u_int_set box_set;
            int pos = i * N * HEIGHT + j * WIDTH;
            for (int k = 0; k < HEIGHT; k++) {
                for (int l = 0; l < WIDTH; l++) {
                    box_set.insert(pos + k * N + l);
                }
            }
            sudoku_solver::get_constraints().push_back(box_set);
        }
    }
}

void sudoku_solver::generate_neighbors() const {
    for (int i = 0; i < N * N; i++) {
        u_int_set neighbor_set;
        for (const auto& constraint : sudoku_solver::get_constraints()) {
            if (constraint.count(i) == 1) {
                for (const int& neighbor : constraint) {
                    neighbor_set.insert(neighbor);
                }
            }
        }
        neighbor_set.erase(i);
        sudoku_solver::get_neighbors().push_back(neighbor_set);
    }
}

void sudoku_solver::generate_symbols() const {
    for (int i = 0; i < N; i++) {
        sudoku_solver::get_symbols().insert("123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i]);
    }
}

sudoku sudoku_solver::solve_sudoku(sudoku puzzle) const {
    if (!puzzle.is_valid()) {
        return puzzle;
    }
    if (puzzle.is_solved()) {
        return puzzle;
    }

    int min_possible_n = N + 1;
    int min_possible_i = -1;
    const u_char_set* min_possible_symbols_ptr;
    for (const auto& pair : puzzle.get_possible_symbols()) {
        const int& i = pair.first;
        const u_char_set& symbols = pair.second;
        if (symbols.size() < min_possible_n) {
            min_possible_n = symbols.size();
            min_possible_i = i;
            min_possible_symbols_ptr = &symbols;
        }
        if (min_possible_n == 1) {
            break;
        }
    }

    for (const char& symbol : *min_possible_symbols_ptr) {
        sudoku result = solve_sudoku(puzzle.replace(min_possible_i, symbol));
        if (result.get_puzzle().size() != 0) {
            return result;
        }
    }

    const static sudoku empty_puzzle;
    return empty_puzzle;
}

/* public */
sudoku_solver::sudoku_solver() {
    generate_constraints();
    generate_neighbors();
    generate_symbols();
}
const sudoku& sudoku_solver::get_puzzle() const {
    return puzzle;
};

sudoku sudoku_solver::get_solution() const {
    return solve_sudoku(puzzle);
}

void sudoku_solver::set_puzzle(const std::string& puzzle) {
    set_puzzle(sudoku(puzzle));
}

void sudoku_solver::set_puzzle(const sudoku& puzzle) {
    this->puzzle = puzzle;
}

bool sudoku_solver::check_puzzle() const {
    if (!puzzle.is_valid()) {
        return false;
    }
    for (const auto& constraint : sudoku_solver::get_constraints()) {
        u_char_set constraint_symbols;
        for (const int& i : constraint) {
            if (puzzle.get_puzzle()[i] == '_') {
                continue;
            }
            if (constraint_symbols.count(puzzle.get_puzzle()[i]) == 1) {
                return false;
            }
            constraint_symbols.insert(puzzle.get_puzzle()[i]);
        }
    }
    return true;
}