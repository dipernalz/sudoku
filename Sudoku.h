#include <string>

using namespace std;

class Sudoku {
   private:
    string puzzle;
    const static int N = 9;

   public:
    Sudoku() = default;

    Sudoku(string puzzle) {
        this->puzzle = puzzle;
    }

    string get_puzzle() {
        return puzzle;
    }

    Sudoku replace(int index, char symbol) {
        char temp[N * N];
        puzzle.copy(temp, N * N, 0);
        temp[index] = symbol;
        return Sudoku(temp);
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
};

class SudokuSolver {
   private:
    Sudoku sudoku;
    vector<unordered_set<int>> constraints;
    vector<unordered_set<int>> neighbors;
    unordered_set<int> symbols;
    const static int N = 9;
    const static int WIDTH = 3;
    const static int HEIGHT = 3;

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
        sudoku.print();

        bool spaceFound = false;
        for (int i = 0; i < N * N; i++) {
            if (sudoku.get_puzzle().at(i) == '_') {
                spaceFound = true;
                for (char symbol : symbols) {
                    bool symbolIsValid = true;
                    for (int position : neighbors.at(i)) {
                        if (sudoku.get_puzzle().at(position) == symbol) {
                            symbolIsValid = false;
                            break;
                        }
                    }
                    if (symbolIsValid) {
                        Sudoku result = solve_sudoku(sudoku.replace(i, symbol));
                        if (result.get_puzzle().length() != 0) {
                            return result;
                        }
                    }
                }
            }
        }
        if (!spaceFound) {
            return sudoku;
        }
        return Sudoku("");
    }

    void generate_symbols() {
        string possible_symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 1; i <= N; i++) {
            symbols.insert(possible_symbols.at(i));
        }
    }

   public:
    SudokuSolver(string puzzle) : SudokuSolver(Sudoku(puzzle)) {}

    SudokuSolver(Sudoku sudoku) {
        this->sudoku = sudoku;
        sudoku.print();

        generate_constraints();
        generate_neighbors();
        generate_symbols();
    }

    Sudoku solve() {
        return solve_sudoku(sudoku);
    }
};
