#include <iostream>

#define N 9

using namespace std;

void print(int board[][N]) {
    cout << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";

            if ((j+1) % 3 == 0 && (j+1) != N) {
                cout << " |  ";
            }
        }

        if ((i+1) % 3 == 0 && (i+1) != N) {
            cout << endl;
            cout << "-------------------------";
        }

        if (i+1 != N) cout << endl << "       |         |" << endl;
    }

    cout << endl << endl;
}

void next_empty(int board[][N], int& x, int& y) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                x = i;
                y = j;
                return;
            }
        }
    }
}

bool any_empty(int board[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                return true;
            }
        }
    }

    return false;
}

bool valid_move(int x, int y, int v, int board[][N]) {
    if (board[x][y] != 0) {
        return false;
    }

    for (int i = 0; i < N; i++) {
        if (board[x][i] == v) return false;
    }

    for (int i = 0; i < N; i++) {
        if (board[i][y] == v) return false;
    }

    for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++) {
        for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++) {
            if (board[i][j] == v) {
                return false;
            }
        }
    }

    return true;
}

bool solvable(int board[][N]) {
    if (!any_empty(board))
        return true;

    int x, y;
    next_empty(board, x, y);

    for (int k = 1; k <= 9; k++) {
        if (valid_move(x, y, k, board)) {
            board[x][y] = k;

            if (solvable(board)) {
                return true;
            }

            board[x][y] = 0;
        }

    }

    board[x][y] = 0;

    return false;
}

void board_copy(int board[][N], int copy[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            copy[i][j] = board[i][j];
        }
    }
}

int main() {
    int board[N][N];
    int copy[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    cout << endl;
    cout << "                   Welcome to" << endl;
    cout << "         U L T I M A T E   D U I D O K U" << endl << endl << endl;

    cout << "A game explained to the author by Professor Kaushik Basu" << endl << endl;
    cout << "Author: Luis Hoderlein" << endl << endl;

    cout << "Rules / Information: " << endl;
    cout << "1. Fill in the tiles as if this was sudoku" << endl;
    cout << "2. If a player\'s move leads to an unsolvable board, " << endl;
    cout << "       that player loses" << endl;
    cout << "3. If the board is solved, the game is a tie" << endl;
    cout << "4. 0\'s are fields which have no values yet " << endl << endl;

    while (any_empty(board)) {
        cout << "It is player 1\'s turn." << endl;

        print(board);

        bool valid = false;
        int adj_row = -1, adj_col = -1, adj_val = -1;

        while (!valid) {
            cout << "row: ";

            string row;
            cin >> row;
            adj_row = atoi(row.c_str()) - 1;

            cout << "col: ";

            string col;
            cin >> col;
            adj_col = atoi(col.c_str()) - 1;

            cout << "val: ";

            string val;
            cin >> val;
            adj_val = atoi(val.c_str());

            if (adj_row < 0 || adj_row > N-1) {
                cout << "invalid row: " << row << endl << endl;
            } else if (adj_col < 0 || adj_col > N-1) {
                cout << "invalid col: " << col << endl << endl;
            } else if (adj_val <= 0 || adj_row > 9) {
                cout << "invalid val: " << val << endl << endl;
            } else if (!valid_move(adj_row, adj_col, adj_val, board)) {
                cout << "invalid move: " << row << " " << col << " " << val << endl << endl;
            } else {
                valid = true;
                cout << endl;
            }
        }

        board[adj_row][adj_col] = adj_val;
        board_copy(board, copy);
        bool slv = solvable(copy);

        if (!slv) {
            cout << "player 1 loses! There are no more valid moves!" << endl;
            cout << "final state of the board: " << endl << endl;

            print(board);
            return 2;
        }

        if (any_empty(board)) {
            cout << "It is player 2\'s turn." << endl;

            print(board);

            valid = false;
            adj_row = -1, adj_col = -1, adj_val = -1;

            while (!valid) {
                cout << "row: ";

                string row;
                cin >> row;
                adj_row = atoi(row.c_str()) - 1;

                cout << "col: ";

                string col;
                cin >> col;
                adj_col = atoi(col.c_str()) - 1;

                cout << "val: ";

                string val;
                cin >> val;
                adj_val = atoi(val.c_str());

                if (adj_row < 0 || adj_row > N-1) {
                    cout << "invalid row: " << row << endl << endl;
                } else if (adj_col < 0 || adj_col > N-1) {
                    cout << "invalid col: " << col << endl << endl;
                } else if (adj_val <= 0 || adj_row > 9) {
                    cout << "invalid val: " << val << endl << endl;
                } else if (!valid_move(adj_row, adj_col, adj_val, board)) {
                    cout << "invalid move: " << row << " " << col << " " << val << endl << endl;
                } else {
                    valid = true;
                    cout << endl;
                }
            }

            board[adj_row][adj_col] = adj_val;
            board_copy(board, copy);
            slv = solvable(copy);

            if (!slv) {
                cout << "player 2 loses! There are no more valid moves!" << endl;
                cout << "final state of the board: " << endl << endl;
                print(board);
                return 1;
            }
        }
    }

    cout << "It is a tie!" << endl;
    cout << "final state of the board: " << endl << endl;
    print(board);

    return 0;
}