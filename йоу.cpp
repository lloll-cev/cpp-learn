#include <iostream>  
#include <array>  
#include <string>  
#include <limits>  
#include <vector>  
#include <random>  
#include <cctype>  

using namespace std;

const array<array<int, 3>, 8> winningCombinations = {
    array<int, 3>{0, 1, 2},
    array<int, 3>{3, 4, 5},
    array<int, 3>{6, 7, 8},
    array<int, 3>{0, 3, 6},
    array<int, 3>{1, 4, 7},
    array<int, 3>{2, 5, 8},
    array<int, 3>{0, 4, 8},
    array<int, 3>{2, 4, 6}
};

const string RED = "\x1b[91m";
const string CYAN = "\x1b[96m";
const string RESET = "\x1b[0m";

string colorCell(const string& cell) {
    if (cell == "X") {
        return RED + cell + RESET;
    }

    if (cell == "O") {
        return CYAN + cell + RESET;
    }

    return cell;
}

void displayBoard(
    const array<string, 9>& currentBoard
) {
    array<string, 9> coloredBoard;

    for (int i = 0; i < 9; i++) {
        coloredBoard[i] = colorCell(currentBoard[i]);
    }

    cout
        << " " << coloredBoard[0] << " | "
        << coloredBoard[1] << " | "
        << coloredBoard[2] << "\n"

        << "---+---+---\n"

        << " " << coloredBoard[3] << " | "
        << coloredBoard[4] << " | "
        << coloredBoard[5] << "\n"

        << "---+---+---\n"

        << " " << coloredBoard[6] << " | "
        << coloredBoard[7] << " | "
        << coloredBoard[8] << "\n";
}

void makeMove(
    array<string, 9>& board,
    int cellNumber,
    char playerSymbol
) {
    int index = cellNumber - 1;

    board[index] = playerSymbol;
}

bool isValidCellNumber(int cellNumber) {
    return cellNumber >= 1 && cellNumber <= 9;
}

bool isCellFree(
    const array<string, 9>& board,
    int cellNumber
) {
    int index = cellNumber - 1;

    if (board[index] != "X" && board[index] != "O") {
        return true;
    }

    return false;
}

char switchPlayer(char currentPlayer) {
    if (currentPlayer == 'X') {
        return 'O';
    }

    return 'X';
}

bool checkWinner(
    const array<string, 9>& currentBoard,
    char playerSymbol
) {
    for (const array<int, 3> &combination : winningCombinations) {
        int firstIndex = combination[0];
        int secondIndex = combination[1];
        int thirdIndex = combination[2];

        if (
            currentBoard[firstIndex][0] == playerSymbol &&
            currentBoard[secondIndex][0] == playerSymbol &&
            currentBoard[thirdIndex][0] == playerSymbol
            ) {
            return true;
        }
    }

    return false;
}

array<string, 9> createBoard() {
    return {
        "1", "2", "3",
        "4", "5", "6",
        "7", "8", "9"
    };
}

int chooseGameMode() {
    while (true) {
        int mode;

        cout
            << "Choose a game mode:\n"
            << "\n"
            << "1 - Two players\n"
            << "2 - Play against the computer\n"
            << ": ";

        cin >> mode;

        if (
            cin.good() &&
            cin.peek() == '\n' &&
            (mode == 1 || mode == 2)
            ) {
            return mode;
        }

        cout << "Enter 1 or 2.\n";

        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }
}

int getComputerMove(
    const array<string, 9>& currentBoard
) {
    vector<int> free;

    for (const string& item : currentBoard) {
        if (item != "X" && item != "O") {
            free.push_back(stoi(item));
        }
    }

    static random_device randomDevice;
    static mt19937 generator(randomDevice());

    uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(free.size()) - 1
    );

    int index = distribution(generator);

    return free[index];
}


void displayGameScreen(
    const array<string, 9>& currentBoard,
    int mode,
    char currentPlayer
) {
    cout << "\x1b[2J\x1b[H";

    string modeName = "Two players";
    string turnText = "Player ";

    turnText += currentPlayer;

    if (mode == 2) {
        modeName = "Against the computer";
    }

    if (mode == 2 && currentPlayer == 'O') {
        turnText = "Computer (O)";
    }

    cout
        << "=========================\n"
        << "       TIC-TAC-TOE\n"
        << "=========================\n"
        << "\n"
        << "Mode: " << modeName << "\n"
        << "Turn: " << turnText << "\n"
        << "\n";

    displayBoard(currentBoard);
}

void playRound() {
    int mode = chooseGameMode();

    array<string, 9> board = createBoard();
    char currentPlayer = 'X';
    int movesCount = 0;

    displayGameScreen(board, mode, currentPlayer);

    while (movesCount < 9) {
        int cellNumber;

        if (mode == 2 && currentPlayer == 'O') {
            cellNumber = getComputerMove(board);

            cout << "The computer chose cell " << cellNumber << ".\n";
        }
        else {
            cout << "Player " << currentPlayer << ", choose a cell: ";

            cin >> cellNumber;

            if (!(cin.good() && cin.peek() == '\n')) {
                cout << "Enter a whole number from 1 to 9!\n";

                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                continue;
            }
        }

        if (!isValidCellNumber(cellNumber)) {
            cout << "Enter a whole number from 1 to 9!\n";
            continue;
        }

        if (!isCellFree(board, cellNumber)) {
            cout << "This cell is occupied. " << "Choose another cell!\n";

            continue;
        }

        makeMove(board, cellNumber, currentPlayer);

        movesCount++;

        if (checkWinner(board, currentPlayer)) {
            displayGameScreen(board, mode, currentPlayer);

            cout << "Player " << currentPlayer << " wins!\n";

            break;
        }

        if (movesCount == 9) {
            displayGameScreen(board, mode, currentPlayer);

            cout << "Draw!\n";
            break;
        }

        currentPlayer = switchPlayer(currentPlayer);

        displayGameScreen(board, mode, currentPlayer);
    }
}

void startGame() {
    string playAgain = "yes";

    while (playAgain == "yes") {
        playRound();

        cout << "Play again? (yes/no): ";

        string answer;
        cin >> answer;

        for (char& character : answer) {
            character = static_cast<char>(
                tolower(
                    static_cast<unsigned char>(character)
                )
                );
        }

        playAgain = answer;
    }
}

int main() {
    startGame();

    return 0;
}
