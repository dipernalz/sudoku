#include "sudoku_solver.h"

#include <iostream>
#include <string>
#include <unordered_set>

#include "sudoku.h"

void sudoku_solver::generate_constraints() {
    for (int i = 0; i < N; i++) {
        std::unordered_set<int> column_set;
        for (int j = i; j < N * N; j += N) {
            column_set.insert(j);
        }
        sudoku_solver::get_constraints().push_back(column_set);
    }
    for (int i = 0; i < N * N; i += N) {
        std::unordered_set<int> row_set;
        for (int j = i; j < i + N; j++) {
            row_set.insert(j);
        }
        sudoku_solver::get_constraints().push_back(row_set);
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::unordered_set<int> box_set;
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

void sudoku_solver::generate_neighbors() {
    for (int i = 0; i < N * N; i++) {
        std::unordered_set<int> neighbor_set;
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

void sudoku_solver::generate_symbols() {
    for (int i = 0; i < N; i++) {
        sudoku_solver::get_symbols().insert("123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i]);
    }
}

const sudoku sudoku_solver::solve_sudoku(const sudoku& puzzle) {
    if (puzzle.get_puzzle().size() == 0) {
        return puzzle;
    }

    if (puzzle.get_possible_symbols().size() == 0) {
        return puzzle;
    }

    int min_possible_n = N + 1;
    int min_possible_pos = -1;
    const std::unordered_set<char>* min_possible_symbols;
    for (const auto& pair : puzzle.get_possible_symbols()) {
        const int& pos = pair.first;
        const std::unordered_set<char>& symbols = pair.second;
        if (symbols.size() < min_possible_n) {
            min_possible_n = symbols.size();
            min_possible_pos = pos;
            min_possible_symbols = &symbols;
        }
    }

    for (const char& symbol : *min_possible_symbols) {
        const sudoku& result = solve_sudoku(puzzle.replace(min_possible_pos, symbol));
        if (result.get_puzzle().size() != 0) {
            return result;
        }
    }
    return empty_puzzle;
}

sudoku_solver::sudoku_solver() {
    generate_constraints();
    generate_neighbors();
    generate_symbols();
}

void sudoku_solver::set_puzzle(const std::string& puzzle) {
    this->puzzle = sudoku(puzzle);
}

void sudoku_solver::set_puzzle(sudoku& sudoku) {
    this->puzzle = sudoku;
}

sudoku sudoku_solver::solve() {
    return solve_sudoku(puzzle);
}
