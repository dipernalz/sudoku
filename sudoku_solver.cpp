#include "sudoku_solver.hpp"

#include "bit_operations.hpp"
#include "sudoku.hpp"

using uint128_t = __uint128_t;

void generate_constraints(uint128_t* constraints) {
    uint8_t constraint_index = 0;
    for (uint8_t i = 0; i < N; i++) {
        for (uint8_t j = i; j < N * N; j += N) {
            turn_on_bit(&constraints[constraint_index], j);
        }
        constraint_index++;
    }
    for (uint8_t i = 0; i < N * N; i += N) {
        for (uint8_t j = i; j < i + N; j++) {
            turn_on_bit(&constraints[constraint_index], j);
        }
        constraint_index++;
    }
    for (uint8_t i = 0; i < HEIGHT; i++) {
        for (uint8_t j = 0; j < WIDTH; j++) {
            uint8_t pos = i * N * HEIGHT + j * WIDTH;
            for (uint8_t k = 0; k < HEIGHT; k++) {
                for (uint8_t l = 0; l < WIDTH; l++) {
                    turn_on_bit(&constraints[constraint_index],
                                pos + k * N + l);
                }
            }
            constraint_index++;
        }
    }
}

void generate_neighbors(uint128_t* neighbors, uint128_t* constraints) {
    for (uint8_t i = 0; i < N * N; i++) {
        for (uint8_t j = 0; j < N * WIDTH; j++) {
            if (is_bit_on(constraints[j], i)) {
                neighbors[i] |= constraints[j];
            }
        }
        turn_off_bit(&neighbors[i], i);
    }
}

void generate_symbols(unsigned char* index_to_symbol,
                      uint8_t* symbol_to_index) {
    const static unsigned char possible_symbols[] =
        "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (uint8_t i = 0; i < N; i++) {
        index_to_symbol[i] = possible_symbols[i];
        symbol_to_index[possible_symbols[i]] = i;
    }
}

sudoku solve_puzzle(sudoku puzzle) {
    const static sudoku null_puzzle;

    if (!puzzle.is_valid()) {
        return null_puzzle;
    }
    if (puzzle.is_solved()) {
        return puzzle;
    }

    uint8_t min_possible_n = N + 1;
    uint8_t min_possible_i = N * N;
    for (uint8_t i = 0; i < N * N; i++) {
        if (puzzle.get_possible_symbols()[i] == 0) {
            continue;
        }
        uint8_t possible_n = count_on_bits(puzzle.get_possible_symbols()[i]);
        if (possible_n < min_possible_n) {
            min_possible_n = possible_n;
            min_possible_i = i;
            if (min_possible_n == 1) {
                break;
            }
        }
    }

    for (uint8_t i = 0; i < N; i++) {
        if (is_bit_on(puzzle.get_possible_symbols()[min_possible_i], i)) {
            sudoku result = solve_puzzle(puzzle.replace(min_possible_i, i));
            if (result.is_solved()) {
                return result;
            }
        }
    }

    return null_puzzle;
}

bool check_puzzle(sudoku puzzle, uint128_t* constraints) {
    if (!puzzle.is_valid()) {
        return false;
    }
    for (uint8_t i = 0; i < N * WIDTH; i++) {
        uint16_t constraint_symbols = 0;
        for (uint8_t j = 0; j < N * N; j++) {
            if (!is_bit_on(constraints[i], j)) {
                continue;
            }
            for (uint8_t k = 0; k < N; k++) {
                if (is_bit_on(puzzle.get_puzzle()[k], j)) {
                    if (is_bit_on(constraint_symbols, k)) {
                        return false;
                    }
                    turn_on_bit(&constraint_symbols, k);
                }
            }
        }
    }
    return true;
}
