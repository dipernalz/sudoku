#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class sudoku {
   private:
    std::string puzzle;
    std::unordered_map<int, std::unordered_set<char>> possible_symbols;

    sudoku(const std::string& puzzle,
           const std::unordered_map<int, std::unordered_set<char>>* const possible_symbols);

   public:
    enum { N = 9 };
    enum { WIDTH = 3 };
    enum { HEIGHT = 3 };

    sudoku();

    sudoku(const std::string& puzzle);

    const std::string& get_puzzle() const;

    const std::unordered_map<int, std::unordered_set<char>>& get_possible_symbols() const;

    sudoku replace(const int& index, const char& symbol) const;

    void print_grid() const;

    void print_line() const;
};

#endif
