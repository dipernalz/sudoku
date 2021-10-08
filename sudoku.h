using namespace std;

const static int N = 9;
const static int WIDTH = 3;
const static int HEIGHT = 3;
static vector<unordered_set<int>> CONSTRAINTS;
static vector<unordered_set<int>> NEIGHBORS;
static unordered_set<char> SYMBOLS;

class sudoku {
   private:
    string puzzle;
    unordered_map<int, unordered_set<char>> possible_symbols;

    sudoku(const string& puzzle, const unordered_map<int, unordered_set<char>>* const possible_symbols) {
        this->puzzle = puzzle;
        this->possible_symbols = *possible_symbols;
    }

   public:
    sudoku() {
        this->puzzle = "";
    };

    sudoku(const string& puzzle) {
        this->puzzle = puzzle;

        for (int i = 0; i < N * N; i++) {
            if (puzzle[i] == '_') {
                possible_symbols[i];
                for (const char& symbol : SYMBOLS) {
                    bool symbolIsValid = true;
                    for (const int& pos : NEIGHBORS[i]) {
                        if (puzzle[pos] == symbol) {
                            symbolIsValid = false;
                            break;
                        }
                    }
                    if (symbolIsValid) {
                        possible_symbols[i].insert(symbol);
                    }
                }
            }
        }
    }

    const string& get_puzzle() const {
        return puzzle;
    }

    const unordered_map<int, unordered_set<char>>& get_possible_symbols() const {
        return possible_symbols;
    }

    sudoku replace(const int& index, const char& symbol) const {
        string new_puzzle = puzzle;
        new_puzzle[index] = symbol;
        unordered_map<int, unordered_set<char>> new_possible_symbols;
        for (const auto& pair : possible_symbols) {
            const int& pos = pair.first;
            if (index == pos) {
                continue;
            }
            new_possible_symbols[pos] = pair.second;
            if (NEIGHBORS[index].count(pos) == 1) {
                new_possible_symbols[pos].erase(symbol);
            }
            if (new_possible_symbols[pos].size() == 0) {
                return sudoku();
            }
        }
        return sudoku(new_puzzle, &new_possible_symbols);
    }

    void print_grid() const {
        if (puzzle.size() == 0) {
            return;
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << puzzle[i * N + j];
                if (j != N - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    void print_line() const {
        if (puzzle.size() == 0) {
            return;
        }
        cout << puzzle << endl;
    }
};
