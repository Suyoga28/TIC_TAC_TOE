#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function prototypes
void initializeBoard(int size);
void printBoard();
bool makeMove(int row, int col, char player);
bool checkWin(char player);
bool checkDraw();

// Global variables
vector<vector<char>> board;

int main() {
    int size;
    cout<<"_____________________________________________________________________________________________________";
    cout << "\n\nEnter the size of the board (e.g., 3 for traditional Tic Tac Toe): ";
    cin >> size;

    initializeBoard(size);
    printBoard();

    char currentPlayer = 'X';
    int row, col;
    bool win = false;
    bool draw = false;

    while (!win && !draw) {
        cout << "\nPlayer " << currentPlayer << ", enter your move (row column): ";
        cin >> row >> col;

        if (row < 1 || row > size || col < 1 || col > size || board[row - 1][col - 1] != ' ') {
            cout << "\nInvalid move. Keep trying.\n\n";
            continue;
        }

        if (makeMove(row - 1, col - 1, currentPlayer)) {
            win = checkWin(currentPlayer);
            draw = checkDraw();
            printBoard();

            if (win) {
                cout << "Player " << currentPlayer << " wins!\n";
            } else if (draw) {
                cout << "\n It's a draw!\n";
                cout<<"\nInstead of giving up, try again\n";
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    return 0;
}

void initializeBoard(int size) {
    board.clear();
    for (int i = 0; i < size; ++i) {
        vector<char> row(size, ' ');
        board.push_back(row);
    }
}

void printBoard() {
    for (const auto& row : board) {
        for (char cell : row) {
            cout << cell << " | ";
        }
        cout << endl;
    }
}

bool makeMove(int row, int col, char player) {
    if (board[row][col] == ' ') {
        board[row][col] = player;
        return true;
    }
    return false;
}

bool checkWin(char player) {
    int size = board.size();
    // Check rows and columns
    for (int i = 0; i < size; ++i) {
        bool rowWin = true;
        bool colWin = true;
        for (int j = 0; j < size; ++j) {
            if (board[i][j] != player) rowWin = false;
            if (board[j][i] != player) colWin = false;
        }
        if (rowWin || colWin) return true;
    }

    // Check diagonals
    bool diag1Win = true;
    bool diag2Win = true;
    for (int i = 0; i < size; ++i) {
        if (board[i][i] != player) diag1Win = false;
        if (board[i][size - 1 - i] != player) diag2Win = false;
    }
    if (diag1Win || diag2Win) return true;

    return false;
}

bool checkDraw() {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false; // There's an empty cell, game is not a draw yet
            }
        }
    }
    return true; // No empty cell found, it's a draw
}
