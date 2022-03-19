#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>

#include "bit_operations.hpp"

using uint128_t = __uint128_t;

class sudoku {
   private:
    uint128_t puzzle[N] = {0};
    uint16_t possible_symbols[N * N] = {0};
    uint128_t spaces = ~0;
    unsigned char* index_to_symbol = NULL;
    uint128_t* neighbors = NULL;

    sudoku(uint128_t* const puzzle, uint16_t* const possible_symbols,
           const uint128_t& spaces, unsigned char* const index_to_symbol,
           uint128_t* const neighbors);

   public:
    sudoku();

    sudoku(const std::string puzzle, unsigned char* const index_to_symbol,
           uint128_t* const neighbors, uint8_t* const symbol_to_index);

    sudoku replace(const uint8_t& index, const uint8_t& symbol);

    bool is_solved();

    bool is_valid();

    uint128_t* get_puzzle();

    uint16_t* get_possible_symbols();

    void print();

    void print_grid();
};

#endif
