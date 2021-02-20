#include "Node.h"

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <cmath>
using namespace std;

Node* expand(Node* node, set<vector<vector<int>>> repeats) {
    int row = 0;
    int column = 0;

    // Finding blank (0) in the provided puzzle
    for (unsigned i = 0; i < node->puzzle.size(); ++i) {
        for (unsigned j = 0; j < node->puzzle.size(); ++j) {
            if (node->puzzle[i][j] == 0) {
                row = i;
                column = j;
            }
        }
    }

    // Depth first search of puzzle
    // Order: left, right, up, down

    // Left
    if (column > 0) {
        vector<vector<int>> l = node->puzzle;
        swap(l[row][column], l[row][column - 1]);

        if (repeats.find(l) == repeats.end()) {
            node->childLeft = new Node(l);
        }
    }

    // Right
    if (column < (node->puzzle.size() - 1)) {
        vector<vector<int>> r = node->puzzle;
        swap(r[row][column], r[row][column + 1]);

        if (repeats.find(r) == repeats.end()) {
            node->childRight = new Node(r);
        }
    }

    // Up
    if (row > 0) {
        vector<vector<int>> u = node->puzzle;
        swap(u[row][column], u[row - 1][column]);

        if (repeats.find(u) == repeats.end()) {
            node->childUp = new Node(u);
        }
    }

    // Down
    if (row < (node->puzzle.size() - 1)) {
        vector<vector<int>> d = node->puzzle;
        swap(d[row][column], d[row + 1][column]);

        if (repeats.find(d) == repeats.end()) {
            node->childDown = new Node(d);
        }
    }

    return node;
}

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
                ++heuristic;
            }
        }
    }

    return heuristic;
}

int manhattan(vector<vector<int>> problem) {
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    int heuristic = 0; // Heuristic value

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

void generalSearch(vector<vector<int>> problem, int func) {
    int heuristic = 0; // Heuristic value
    int expanded = 0; // Number of expanded nodes
    int maxSize = 0; // Max size of queue
    int size = 0; // Size of queue

    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    queue<Node*> pQ; // Queue of nodes
    set<vector<vector<int>>> pS; // Set of repeats
    vector<int> heap;
    make_heap(heap.begin(), heap.end());
    stack<int> states;

    if (func == 1) {
        heuristic = uniformCostSearch(problem);
    } else if (func == 2) {
        heuristic = misplaced(problem);
    } else if (func == 3) {
        heuristic = manhattan(problem);
    }

    // Create starting node
    Node* startNode  = new Node(problem);
    startNode->cost = heuristic;

    // Add starting node to queue
    pQ.push(startNode);

    // Increase queue size and max size
    ++maxSize;
    ++size;

    while(pQ.size() > 0) {
        if (func != 1) {

        }

        Node *popNode = pQ.front();
        pQ.pop();

        if (popNode->children == false) {
            popNode->children = true;
            ++expanded;
        }

        --size;

        if (goal == popNode->puzzle) {
            cout << "goalllll" << endl;
        }

        if (expanded != 0) {
            cout << "a" << endl;
        } else{
            cout << "b" << endl;
        }

        Node* expandFunc = expand(popNode, pS);



        //maxSize = fmax(pQ.size(), maxSize);
    }
}

int main() {
    int puzzleType = 0; // Default or DIY
    int algorithmChoice = 0; // UCS, Misplaced, or Manhattan
    vector<vector<int>> puzzle; // 8 puzzle 2d vector
    vector<int> row; // Vector rows for 2d vector initialization
    int size = 3; // 3x3 puzzle, can be changed to make a size x size puzzle
    int diff = 0; // Default difficulty
    int num = 0; // Read in DIY values

    // Initializes vector so it can be filled
    for (unsigned i = 0; i < size; ++i) {
        for (unsigned j = 0; j < size; ++j) {
            row.push_back(0);
        }
        puzzle.push_back(row);
        row.clear();
    }

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
                cin >> num;
                puzzle.at(i).at(j) = num;
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

    generalSearch(puzzle, algorithmChoice);

    return 0;
}