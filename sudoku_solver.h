using namespace std;

class sudoku_solver {
   private:
    sudoku puzzle;
    const sudoku empty_puzzle;

    void generate_constraints() {
        for (int i = 0; i < N; i++) {
            unordered_set<int> column_set;
            for (int j = i; j < N * N; j += N) {
                column_set.insert(j);
            }
            CONSTRAINTS.push_back(column_set);
        }
        for (int i = 0; i < N * N; i += N) {
            unordered_set<int> row_set;
            for (int j = i; j < i + N; j++) {
                row_set.insert(j);
            }
            CONSTRAINTS.push_back(row_set);
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
                CONSTRAINTS.push_back(box_set);
            }
        }
    }

    void generate_neighbors() {
        for (int i = 0; i < N * N; i++) {
            unordered_set<int> neighbor_set;
            for (const auto& constraint : CONSTRAINTS) {
                if (constraint.count(i) == 1) {
                    for (const int& neighbor : constraint) {
                        neighbor_set.insert(neighbor);
                    }
                }
            }
            neighbor_set.erase(i);
            NEIGHBORS.push_back(neighbor_set);
        }
    }

    void generate_symbols() {
        for (int i = 0; i < N; i++) {
            SYMBOLS.insert("123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i]);
        }
    }

    const sudoku solve_sudoku(const sudoku& puzzle) {
        // puzzle.print_line();

        if (puzzle.get_puzzle().size() == 0) {
            return puzzle;
        }

        if (puzzle.get_possible_symbols().size() == 0) {
            return puzzle;
        }

        // skip iterations if possible choices is 1
        int min_possible_n = N + 1;
        int min_possible_pos = -1;
        const unordered_set<char>* min_possible_symbols;
        for (const auto& pair : puzzle.get_possible_symbols()) {
            const int& pos = pair.first;
            const unordered_set<char>& symbols = pair.second;
            if (pair.second.size() < min_possible_n) {
                min_possible_n = symbols.size();
                min_possible_pos = pos;
                min_possible_symbols = &symbols;
            }
        }
        // cout << (*min_possible_symbols).size() << endl;

        for (const char& symbol : *min_possible_symbols) {
            const sudoku& result = solve_sudoku(puzzle.replace(min_possible_pos, symbol));
            if (result.get_puzzle().size() != 0) {
                return result;
            }
        }
        return empty_puzzle;
    }

   public:
    sudoku_solver() {
        generate_constraints();
        generate_neighbors();
        generate_symbols();
    }

    void set_puzzle(const string& puzzle) {
        this->puzzle = sudoku(puzzle);
    }

    void set_puzzle(sudoku& sudoku) {
        this->puzzle = sudoku;
    }

    sudoku solve() {
        return solve_sudoku(puzzle);
    }
};
