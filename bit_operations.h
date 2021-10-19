#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H

#include <iostream>

#include "sudoku_constants.h"

using uint128_t = __uint128_t;

void generate_bitmasks();

uint8_t count_on_bits(uint128_t n);

uint128_t turn_on_bit(const uint128_t& n, const uint8_t& bit);

void turn_on_bit(uint16_t* const n, const uint8_t& bit);

void turn_on_bit(uint128_t* const n, const uint8_t& bit);

uint128_t turn_off_bit(const uint128_t& n, const uint8_t& bit);

void turn_off_bit(uint16_t* const n, const uint8_t& bit);

void turn_off_bit(uint128_t* const n, const uint8_t& bit);

bool is_bit_on(const uint128_t& n, const uint8_t& bit);

void print_binary(const uint128_t& n);

void print_binary(const uint16_t& n);

#endif
