#include "Tree.h"
#include "Node.h"

#include <iostream>
#include <vector>
using namespace std;

bool goal() {
    return true;
}

void expand() {}

int uniformCostSearch(vector<vector<int>> problem) {
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    return 0;
}

int misplaced(vector<vector<int>> problem) {
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    int heuristic = 0;

    for (unsigned i = 0; i < problem.size(); ++i) {
        for (unsigned j = 0; j < problem.size(); ++j) {
            if ((problem[i][j] != 0) && (problem[i][j] != goal[i][j])) {
                heuristic += 1;
            }
        }
    }

    return heuristic;
}

int manhattan(vector<vector<int>> problem) {
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    int heuristic = 0;

    int problemRow = 0;
    int problemColumn = 0;
    int goalRow = 0;
    int goalColumn = 0;

    int rowComp = 0;
    int columnComp = 0;

    for (unsigned i = 0; i < 9; ++i) {
        for (unsigned j = 0; j < problem.size(); ++j) {
            for (unsigned k = 0; k < problem.size(); ++k) {
                if (problem[j][k] == i) {
                    problemRow = j;
                    problemColumn = k;
                }
                if (goal[j][k] == i) {
                    goalRow = j;
                    goalColumn = k;
                }
            }
        }
        rowComp = abs(goalRow - problemRow);
        columnComp = abs(goalColumn - problemColumn);
        heuristic += rowComp - columnComp;
    }

    return heuristic;
}

void generalSearch(vector<vector<int>> problem, int func, Tree *tree) {
    int heuristic = 0;

    if (func == 1) {
        heuristic = uniformCostSearch(problem);
    } else if (func == 2) {
        heuristic = misplaced(problem);
    } else if (func == 3) {
        heuristic = manhattan(problem);
    }

    Node* curr = nullptr;

    tree->insert(heuristic);
}

int main() {
    Tree tree;

    int puzzleType = 0;
    int algorithmChoice = 0;
    vector<vector<int>> puzzle;
    int size = 3; // 3x3 puzzle, can be changed to make a size x size puzzle
    int diff = 0;

    cout << "Welcome to Cristina Lawson's 8-puzzle solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >>  puzzleType;

    if (puzzleType == 1) {
        cout << "You wish to use a default puzzle. Please enter a desired difficulty on a scale from 0 to 5." << endl;
        cin >> diff;

        if (diff == 0) {
            cout << "Difficulty of 'Trivial' selected." << endl;
            puzzle = {{1, 2, 3},{4, 5, 6},{7, 8, 0}};
        } else if (diff == 1) {
            cout << "Difficulty of 'Very Easy' selected." << endl;
            puzzle = {{1, 2, 3},{4, 5, 6},{7, 0, 8}};
        } else if (diff == 2) {
            cout << "Difficulty of 'Easy' selected." << endl;
            puzzle = {{1, 2, 0},{4, 5, 3},{7, 8, 6}};
        } else if (diff == 3) {
            cout << "Difficulty of 'Doable' selected." << endl;
            puzzle = {{0, 1, 2},{4, 5, 3},{7, 8, 6}};
        } else if (diff == 4) {
            cout << "Difficulty of 'Oh Boy' selected." << endl;
            puzzle = {{8, 7, 1},{6, 0, 2},{5, 4, 3}};
        } else if (diff == 5) {
            cout << "Difficulty of 'Impossible' selected." << endl;
        }
    } else if (puzzleType == 2) {

        cout << "Enter your puzzle, use a zero to represent the blank" << endl;

        for (unsigned i = 0; i < size; ++i) {
            cout << "Enter row " << i + 1 << ", use space or tabs between numbers" << endl;
            for (unsigned j = 0; j < size; ++j) {
                cin >> puzzle[i][j];
            }
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

    cout << endl;

    cout << "Enter your choice of algorithm" << endl
         << "  1. Uniform Cost Search" << endl
         << "  2. A* with the Misplaced Tile heuristic" << endl
         << "  3. A* with the Manhattan distance heuristic." << endl;

    cin >> algorithmChoice;

    generalSearch(puzzle, algorithmChoice, &tree);

    return 0;
}