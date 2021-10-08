#include <string>
#include <unordered_map>

using namespace std;

const static int N = 9;
const static int WIDTH = 3;
const static int HEIGHT = 3;
static vector<unordered_set<int>> constraints;
static vector<unordered_set<int>> neighbors;
static unordered_set<char> symbols;

class Sudoku {
   private:
    string puzzle;
    unordered_map<int, unordered_set<char>> possible_symbols;

    Sudoku(string puzzle, unordered_map<int, unordered_set<char>> possible_symbols) {
        this->puzzle = puzzle;
        this->possible_symbols = possible_symbols;
    }

   public:
    Sudoku() = default;

    Sudoku(string puzzle) {
        this->puzzle = puzzle;
        if (puzzle == "") {
            return;
        }

        for (int i = 0; i < N * N; i++) {
            if (puzzle.at(i) == '_') {
                unordered_set<char> i_possible_symbols;
                for (char symbol : symbols) {
                    bool symbolIsValid = true;
                    for (int position : neighbors.at(i)) {
                        if (puzzle.at(position) == symbol) {
                            symbolIsValid = false;
                            break;
                        }
                    }
                    if (symbolIsValid) {
                        i_possible_symbols.insert(symbol);
                    }
                }
                possible_symbols[i] = i_possible_symbols;
            }
        }
    }

    string get_puzzle() {
        return puzzle;
    }

    unordered_map<int, unordered_set<char>> get_possible_symbols() {
        return possible_symbols;
    }

    Sudoku replace(int index, char symbol) {
        string new_puzzle = puzzle;
        new_puzzle[index] = symbol;
        unordered_map<int, unordered_set<char>> new_possible_symbols;
        for (const auto& pair : possible_symbols) {
            int pos = pair.first;
            if (index == pos) {
                continue;
            }
            unordered_set<char> symbols = pair.second;
            if (neighbors[index].count(pos) == 1) {
                symbols.erase(symbol);
            }
            if (symbols.size() == 0) {
                return Sudoku("");
            }
            new_possible_symbols[pos] = symbols;
        }
        return Sudoku(new_puzzle, new_possible_symbols);
    }

    void print() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << puzzle[i * N + j];
                if (j != N - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void print_line() {
        cout << puzzle << endl;
    }
};

class SudokuSolver {
   private:
    Sudoku sudoku;

    void generate_constraints() {
        for (int i = 0; i < N; i++) {
            unordered_set<int> column_set;
            for (int j = i; j < N * N; j += N) {
                column_set.insert(j);
            }
            constraints.push_back(column_set);
        }
        for (int i = 0; i < N * N; i += N) {
            unordered_set<int> row_set;
            for (int j = i; j < i + N; j++) {
                row_set.insert(j);
            }
            constraints.push_back(row_set);
        }
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                unordered_set<int> box_set;
                int pos = i * N * HEIGHT + j * WIDTH;
                for (int k = 0; k < HEIGHT; k++) {
                    for (int l = 0; l < WIDTH; l++) {
                        box_set.insert(pos + k * N + l);
                    }
                }
                constraints.push_back(box_set);
            }
        }
    }

    void generate_neighbors() {
        for (int i = 0; i < N * N; i++) {
            unordered_set<int> neighbor_set;
            for (unordered_set<int> constraint : constraints) {
                if (constraint.count(i) == 1) {
                    for (int neighbor : constraint) {
                        neighbor_set.insert(neighbor);
                    }
                }
            }
            neighbor_set.erase(i);
            neighbors.push_back(neighbor_set);
        }
    }

    Sudoku solve_sudoku(Sudoku sudoku) {
        // sudoku.print_line();
        
        if (sudoku.get_puzzle().size() == 0) {
            return Sudoku("");
        }

        if (sudoku.get_possible_symbols().size() == 0) {
            return sudoku;
        }

        int min_possible_n = N + 1;
        int min_possible_pos = -1;
        unordered_set<char> min_possible_symbols;
        for (const auto& pair : sudoku.get_possible_symbols()) {
            int pos = pair.first;
            unordered_set<char> symbols = pair.second;
            if (symbols.size() < min_possible_n) {
                min_possible_n = symbols.size();
                min_possible_pos = pos;
                min_possible_symbols = symbols;
            }
        }

        for (const char symbol : min_possible_symbols) {
            Sudoku result = solve_sudoku(sudoku.replace(min_possible_pos, symbol));
            if (result.get_puzzle().length() != 0) {
                return result;
            }
        }

        return Sudoku("");
    }

    void generate_symbols() {
        string possible_symbols = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < N; i++) {
            symbols.insert(possible_symbols.at(i));
        }
    }

   public:
    SudokuSolver(string puzzle) {
        generate_constraints();
        generate_neighbors();
        generate_symbols();

        this->sudoku = Sudoku(puzzle);
        sudoku.print();
    }

    Sudoku solve() {
        return solve_sudoku(sudoku);
    }
};
