#include "sudoku.hpp"

#include <string>

#include "bit_operations.hpp"

using uint128_t = __uint128_t;

sudoku::sudoku(uint128_t* const puzzle, uint16_t* const possible_symbols,
               const uint128_t& spaces, unsigned char* const index_to_symbol,
               uint128_t* const neighbors) {
    for (uint8_t i = 0; i < N; i++) {
        this->puzzle[i] = puzzle[i];
    }
    for (uint8_t i = 0; i < N * N; i++) {
        this->possible_symbols[i] = possible_symbols[i];
    }
    this->spaces = spaces;
    this->index_to_symbol = index_to_symbol;
    this->neighbors = neighbors;
}

sudoku::sudoku() {
    puzzle[0] = ~0;
}

sudoku::sudoku(const std::string puzzle, unsigned char* const index_to_symbol,
               uint128_t* const neighbors, uint8_t* const symbol_to_index) {
    if (puzzle.size() != N * N) {
        throw std::invalid_argument("puzzle size is invalid");
    }

    this->index_to_symbol = index_to_symbol;
    this->neighbors = neighbors;
    for (uint8_t i = 0; i < N * N; i++) {
        if (puzzle[i] == '_') {
            turn_off_bit(&(this->spaces), i);
            continue;
        }
        uint8_t symbol_index = symbol_to_index[puzzle.at(i)];
        turn_on_bit(&(this->puzzle[symbol_index]), i);
    }
    for (uint8_t i = 0; i < N * N; i++) {
        if (puzzle[i] != '_') {
            continue;
        }
        for (uint8_t j = 0; j < N; j++) {
            if (!(neighbors[i] & this->puzzle[j])) {
                turn_on_bit(&(possible_symbols[i]), j);
            }
        }
    }
}

sudoku sudoku::replace(const uint8_t& index, const uint8_t& symbol) {
    const static sudoku null_puzzle;

    uint128_t new_puzzle[N];
    for (uint8_t i = 0; i < N; i++) {
        new_puzzle[i] = puzzle[i];
    }
    turn_on_bit(&(new_puzzle[symbol]), index);

    uint16_t new_possible_symbols[N * N] = {0};
    for (uint8_t i = 0; i < N * N; i++) {
        if (i == index) {
            continue;
        }
        if (is_bit_on(neighbors[i], index)) {
            new_possible_symbols[i] = turn_off_bit(possible_symbols[i], symbol);
            if (new_possible_symbols[i] == 0 && !is_bit_on(spaces, i)) {
                return null_puzzle;
            }
        } else {
            new_possible_symbols[i] = possible_symbols[i];
        }
    }

    uint128_t new_spaces = turn_on_bit(spaces, index);

    return sudoku(new_puzzle, new_possible_symbols, new_spaces, index_to_symbol,
                  neighbors);
}

bool sudoku::is_solved() {
    return is_valid() && ~spaces == 0;
}

bool sudoku::is_valid() {
    return puzzle[0] != ~0;
}

uint128_t* sudoku::get_puzzle() {
    return puzzle;
}

uint16_t* sudoku::get_possible_symbols() {
    return possible_symbols;
}

void sudoku::print() {
    if (!is_valid()) {
        std::cout << "null puzzle" << std::endl;
        return;
    }
    for (uint8_t i = 0; i < N * N; i++) {
        bool is_space = true;
        for (uint8_t j = 0; j < N; j++) {
            if (is_bit_on(puzzle[j], i)) {
                std::cout << index_to_symbol[j];
                is_space = false;
                break;
            }
        }
        if (is_space) {
            std::cout << '_';
        }
    }
    std::cout << std::endl;
}

void sudoku::print_grid() {
    if (!is_valid()) {
        std::cout << "null puzzle" << std::endl;
        return;
    }
    for (uint8_t i = 0; i < N * N; i++) {
        bool is_space = true;
        for (uint8_t j = 0; j < N; j++) {
            if (is_bit_on(puzzle[j], i)) {
                std::cout << index_to_symbol[j];
                is_space = false;
                break;
            }
        }
        if (is_space) {
            std::cout << '_';
        }
        if (i % N == N - 1) {
            std::cout << std::endl;
        } else {
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
}
