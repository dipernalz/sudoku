#include "sudoku.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "sudoku_solver.h"

sudoku::sudoku(const std::string& puzzle,
               const std::unordered_map<int, std::unordered_set<char>>* const possible_symbols) {
    this->puzzle = puzzle;
    this->possible_symbols = *possible_symbols;
}

sudoku::sudoku() {
    this->puzzle = "";
};

sudoku::sudoku(const std::string& puzzle) {
    this->puzzle = puzzle;

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

const std::string& sudoku::get_puzzle() const {
    return puzzle;
}

const std::unordered_map<int, std::unordered_set<char>>& sudoku::get_possible_symbols() const {
    return this->possible_symbols;
}

sudoku sudoku::replace(const int& index, const char& symbol) const {
    std::string new_puzzle = puzzle;
    new_puzzle[index] = symbol;
    std::unordered_map<int, std::unordered_set<char>> new_possible_symbols;
    for (const auto& pair : possible_symbols) {
        const int& pos = pair.first;
        if (index == pos) {
            continue;
        }
        new_possible_symbols[pos] = pair.second;
        if (sudoku_solver::get_neighbors()[index].count(pos) == 1) {
            new_possible_symbols[pos].erase(symbol);
        }
        if (new_possible_symbols[pos].size() == 0) {
            return sudoku();
        }
    }
    return sudoku(new_puzzle, &new_possible_symbols);
}

void sudoku::print_grid() const {
    if (puzzle.size() == 0) {
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
    if (puzzle.size() == 0) {
        return;
    }
    std::cout << puzzle << std::endl;
}
