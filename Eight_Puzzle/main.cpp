#include <iostream>

using namespace std;

bool goal() {
    return true;
}

void expand() {}

void uniformCostSearch() {}

void misplaced() {}

void manhattan() {}

int main() {

    int puzzleType = 0;
    int algorithmChoice = 0;
    int puzzle[3][3];
    int size = 3; // 3x3 puzzle, can be changed to make a size x size puzzle
    int prev = -1;

    cout << "Welcome to Cristina Lawson's 8-puzzle solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >>  puzzleType;

    if (puzzleType == 1) {

    } else if (puzzleType == 2) {

        cout << "Enter your puzzle, use a zero to represent the blank" << endl;

        for (unsigned i = 0; i < size; ++i) {
            cout << "Enter row " << i + 1 << ", use space or tabs between numbers" << endl;
            for (unsigned j = 0; j < size; ++j) {
                cin >> puzzle[i][j];
            }
        }

        for (unsigned i = 0; i < size; ++i) {
            for (unsigned j = 0; j < size; ++j) {
                cout << puzzle[i][j];

                if (j < size - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    cout << endl;

    cout << "Enter your choice of algorithm" << endl
         << "  1. Uniform Cost Search" << endl
         << "  2. A* with the Misplaced Tile heuristic" << endl
         << "  3. A* with the Manhattan distance heuristic." << endl;

    cin >> algorithmChoice;

    if (algorithmChoice == 1) {
        uniformCostSearch();
    } else if (algorithmChoice == 2) {
        misplaced();
    } else if (algorithmChoice == 3) {
        manhattan();
    }

    return 0;
}