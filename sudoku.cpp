#include "sudoku.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "sudoku_solver.h"

/* private */
sudoku::sudoku(const std::string& puzzle,
               const possible_symbol_map& possible_symbols) {
    exception_check(puzzle);
    this->puzzle = puzzle;
    this->possible_symbols = possible_symbols;
}

void sudoku::generate_possible_symbols() {
    for (int i = 0; i < N * N; i++) {
        if (puzzle[i] == '_') {
            possible_symbols[i];
            for (const char& symbol : sudoku_solver::get_symbols()) {
                bool symbolIsValid = true;
                for (const int& pos : sudoku_solver::get_neighbors()[i]) {
                    if (puzzle[pos] == symbol) {
                        symbolIsValid = false;
                        break;
                    }
                }
                if (symbolIsValid) {
                    possible_symbols[i].insert(symbol);
                }
            }
        }
    }
}

void sudoku::exception_check(const std::string& puzzle) const {
    if (sudoku_solver::get_constraints().size() == 0 ||
        sudoku_solver::get_neighbors().size() == 0 ||
        sudoku_solver::get_symbols().size() == 0) {
        throw std::logic_error("no instance of sudoku_solver has been initialized");
    }
    if (puzzle.size() != N * N) {
        throw std::invalid_argument("puzzle size is invalid");
    }
}

/* public */
sudoku::sudoku(){};

sudoku::sudoku(const std::string& puzzle) {
    exception_check(puzzle);
    this->puzzle = puzzle;
    generate_possible_symbols();
}

bool sudoku::is_valid() const {
    return puzzle.size() == N * N;
}

bool sudoku::is_solved() const {
    return is_valid() && possible_symbols.size() == 0;
}

sudoku sudoku::replace(const int& i, const char& symbol) const {
    std::string new_puzzle = puzzle;
    new_puzzle[i] = symbol;
    possible_symbol_map new_possible_symbols;
    for (const auto& pair : possible_symbols) {
        const int& j = pair.first;
        if (i == j) {
            continue;
        }
        new_possible_symbols[j] = pair.second;
        if (sudoku_solver::get_neighbors()[i].count(j) == 1) {
            new_possible_symbols[j].erase(symbol);
        }
        if (new_possible_symbols[j].size() == 0) {
            static const sudoku empty_puzzle;
            return empty_puzzle;
        }
    }
    return sudoku(new_puzzle, new_possible_symbols);
}

const std::string& sudoku::get_puzzle() const {
    return puzzle;
}

const possible_symbol_map& sudoku::get_possible_symbols() const {
    return possible_symbols;
}

void sudoku::print_grid() const {
    if (!is_valid()) {
        return;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << puzzle[i * N + j];
            if (j != N - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void sudoku::print_line() const {
    if (!is_valid()) {
        return;
    }
    std::cout << puzzle << std::endl;
}
