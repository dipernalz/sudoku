#include "bit_operations.hpp"

#include <iostream>

#include "sudoku_constants.hpp"

static uint128_t on_bitmasks[N * N] = {0};
static uint128_t off_bitmasks[N * N] = {0};

using uint128_t = __uint128_t;

void generate_bitmasks() {
    for (uint8_t i = 0; i < N * N; i++) {
        on_bitmasks[i] = (uint128_t)1 << i;
        off_bitmasks[i] = ~on_bitmasks[i];
    }
}

uint8_t count_on_bits(uint128_t n) {
    uint8_t count = 0;
    while (n) {
        n &= n - 1;
        count++;
    }
    return count;
}

uint128_t turn_on_bit(const uint128_t& n, const uint8_t& bit) {
    return n | on_bitmasks[bit];
}

void turn_on_bit(uint16_t* const n, const uint8_t& bit) {
    *n |= on_bitmasks[bit];
}

void turn_on_bit(uint128_t* const n, const uint8_t& bit) {
    *n |= on_bitmasks[bit];
}

uint128_t turn_off_bit(const uint128_t& n, const uint8_t& bit) {
    return n & off_bitmasks[bit];
}

void turn_off_bit(uint16_t* const n, const uint8_t& bit) {
    *n &= off_bitmasks[bit];
}

void turn_off_bit(uint128_t* const n, const uint8_t& bit) {
    *n &= off_bitmasks[bit];
}

bool is_bit_on(const uint128_t& n, const uint8_t& bit) {
    return (n & on_bitmasks[bit]) != 0;
}

void print_binary(const uint128_t& n) {
    for (int8_t i = N * N - 1; i >= 0; i--) {
        std::cout << ((n & on_bitmasks[i]) != 0);
    }
    std::cout << std::endl;
}

void print_binary(const uint16_t& n) {
    for (int8_t i = N - 1; i >= 0; i--) {
        std::cout << ((n & on_bitmasks[i]) != 0);
    }
    std::cout << std::endl;
}
