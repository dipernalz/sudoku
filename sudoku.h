#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using possible_symbol_map = std::unordered_map<int, std::unordered_set<char>>;

class sudoku {
   private:
    std::string puzzle;
    possible_symbol_map possible_symbols;

    sudoku(const std::string& puzzle,
           const possible_symbol_map& possible_symbols);

    void generate_possible_symbols();

    void exception_check(const std::string& puzzle) const;

   public:
    enum { N = 9,
           WIDTH = 3,
           HEIGHT = 3 };

    sudoku();

    sudoku(const std::string& puzzle);

    bool is_valid() const;

    bool is_solved() const;

    sudoku replace(const int& index, const char& symbol) const;

    const std::string& get_puzzle() const;

    const possible_symbol_map& get_possible_symbols() const;

    void print_grid() const;

    void print_line() const;
};

#endif
