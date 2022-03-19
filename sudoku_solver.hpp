#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include "bit_operations.hpp"
#include "sudoku.hpp"

using uint128_t = __uint128_t;

void generate_constraints(uint128_t* constraints);

void generate_neighbors(uint128_t* neighbors, uint128_t* constraints);

void generate_symbols(unsigned char* index_to_symbol, uint8_t* symbol_to_index);

sudoku solve_puzzle(sudoku puzzle);

bool check_puzzle(sudoku puzzle, uint128_t* constraints);

#endif
