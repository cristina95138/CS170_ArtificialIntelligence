// URL to my code is https://github.com/cristina95138/CS170/tree/main/Eight_Puzzle

#include "Node.h"

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <chrono>
using namespace std;

// Referenced this code for the below sortQueue algorithm. Changed how the queue will be sorted.
// https://www.geeksforgeeks.org/sorting-queue-without-extra-space/
// Finds the index of the minimum node
int minIndex(queue<Node*> &q, int sortedIndex) {
    int minIndex = -1;
    int minVal = INT_MAX;
    int size = q.size();

    for (unsigned i = 0; i < size; ++i) {
        Node* curr = q.front();
        int num = curr->depth + curr->cost;
        q.pop();

        if (num <= minVal && i <= sortedIndex) {
            minIndex = i;
            minVal = num;
        }
        q.push(curr);
    }
    return minIndex;
}

// Inserts the minimum node to the end of the queue
void insert(queue<Node*> &q, int minIndex) {
    Node* minVal;
    int size = q.size();

    for (unsigned i = 0; i < size; ++i) {
        Node* curr = q.front();
        q.pop();

        if (i != minIndex) {
            q.push(curr);
        } else {
            minVal = curr;
        }
    }
    q.push(minVal);
}

// Sorts queue
void sortQueue(queue<Node*> &q) {
    for (unsigned i = 1; i <= q.size(); ++i) {
        int min = minIndex(q, q.size() - i);
        insert(q, min);
    }
}

void goalStatement(int expanded, int maxSize, Node* frontNode, int pSize) {
    // Goal statement
    // Outputs solving metrics when the puzzle reaches its goal state
    // Outputs: amount of expanded nodes, max node in queue, depth of goal node
    cout << "Goal!!" << endl << endl;
    cout << "To solve this problem the search algorithm expanded a total of " <<  expanded << " nodes." << endl;
    cout << "The maximum number of nodes in the queue at any one time was " << maxSize << "." << endl;
    cout << "The depth of the goal node was " << frontNode->depth << "." << endl << endl;

    // Outputs the final state of the goal puzzle so the goal state
    cout << "Final state of the puzzle: " << endl;
    for (unsigned i = 0; i < pSize; ++i) {
        for (unsigned j = 0; j < pSize; ++j) {
            cout << frontNode->puzzle[i][j];

            if (j < pSize - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void stateStatement(int expanded, Node* frontNode, int pSize) {

    /* if expanded == 0 : Outputs the puzzle of the starting node which is the inputted unsolved puzzle
       else : Outputs the puzzle of the node the program is currently at as well as the node's distance to
              the goal/depth of the node (g(n)) and the node's cost to get to the node (h(n)). */

    if (expanded == 0) {
        cout << "Expanding state" << endl;
        for (unsigned i = 0; i < pSize; ++i) {
            for (unsigned j = 0; j < pSize; ++j) {
                cout << frontNode->puzzle[i][j];

                if (j < pSize - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "The best state to expand with a g(n) = " << frontNode->depth << " and h(n) = " << frontNode->cost << " is..." << endl;
        for (unsigned i = 0; i < pSize; ++i) {
            for (unsigned j = 0; j < pSize; ++j) {
                cout << frontNode->puzzle[i][j];

                if (j < pSize - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << "Expanding node..." << endl << endl;
    }
}

// Expands current node into left, right, up, and down node children
Node* expand(Node* node, set<vector<vector<int>>> repeats) {
    int row = 0;
    int column = 0;

    // Finding coordinates of blank (0) in the provided puzzle
    for (unsigned i = 0; i < node->puzzle.size(); ++i) {
        for (unsigned j = 0; j < node->puzzle.size(); ++j) {
            if (node->puzzle[i][j] == 0) {
                row = i;
                column = j;
            }
        }
    }

    // Uniform cost search of puzzle using a BFS-like algorithm
    // Going through each possibility and making a new node until the goal is achieved
    // Order: left, right, up, down

    // Move Left
    if (column > 0) {
        vector<vector<int>> l = node->puzzle;
        swap(l[row][column], l[row][column - 1]);

        if (repeats.find(l) == repeats.end()) {
            node->childLeft = new Node(l);
        }
    }

    // Move Right
    if (column < (node->puzzle.size() - 1)) {
        vector<vector<int>> r = node->puzzle;
        swap(r[row][column], r[row][column + 1]);

        if (repeats.find(r) == repeats.end()) {
            node->childRight = new Node(r);
        }
    }

    // Move Up
    if (row > 0) {
        vector<vector<int>> u = node->puzzle;
        swap(u[row][column], u[row - 1][column]);

        if (repeats.find(u) == repeats.end()) {
            node->childUp = new Node(u);
        }
    }

    // Move Down
    if (row < (node->puzzle.size() - 1)) {
        vector<vector<int>> d = node->puzzle;
        swap(d[row][column], d[row + 1][column]);

        if (repeats.find(d) == repeats.end()) {
            node->childDown = new Node(d);
        }
    }

    return node;
}

// Uniform Cost Search has a heuristic of 0 so just 0 is returned
int uniformCostSearchHeuristic(vector<vector<int>> problem) {
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    return 0;
}

// Misplaced Heuristic Calculation
// Misplaced heuristic is just the amount of pieces in the puzzle that aren't in the same place as the pieces in the goal puzzle
int misplacedHeuristic(vector<vector<int>> problem) {
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

// Manhattan Heuristic Calculation
// Manhattan Distance Formula: m = abs(x2-x1) + abs(y2-y1)
// Manhattan heuristic is the Manhattan distance of the goal pieces from the actual placement of the pieces
int manhattanHeuristic(vector<vector<int>> problem) {
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    int heuristic = 0; // Heuristic value
    int problemRow = 0;
    int problemColumn = 0;
    int goalRow = 0;
    int goalColumn = 0;
    int rowComp = 0;
    int columnComp = 0;

    for (unsigned i = 0; i < 8; ++i) {
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

        heuristic += (rowComp + columnComp);
    }

    return heuristic;
}


// General search algorithm used to implement algorithms with calculated heuristics
void generalSearch(vector<vector<int>> problem, int func, int pSize) {
    int heuristic = 0; // Heuristic value
    int expanded = -1; // Number of expanded nodes
    int maxSize = 0; // Max size of queue
    int size = 0; // Size of queue

    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    queue<Node*> pQ; // Queue of nodes
    set<vector<vector<int>>> pS; // Set of repeats

    // Based on the heuristic chosen by the user, the problem puzzle will be run through one of the algorithms and
    // the heuristic value of the starting node will be determined
    if (func == 1) {
        heuristic = uniformCostSearchHeuristic(problem);
    } else if (func == 2) {
        heuristic = misplacedHeuristic(problem);
    } else if (func == 3) {
        heuristic = manhattanHeuristic(problem);
    }

    // Create starting node
    Node* startNode  = new Node(problem);
    startNode->cost = heuristic;

    // Add starting node to queue and set
    pQ.push(startNode);
    pS.insert(startNode->puzzle);

    // Increase queue size and queue max size
    ++maxSize;
    ++size;

    // While the queue isn't empty the puzzle will be expanded until the goal state is achieved
    while(pQ.size() > 0) {

        // Sort queue for faster run times
        if (func == 2 || func == 3) {
            sortQueue(pQ);
        }

        // Get node at front of the queue and then remove the node from the queue
        Node *frontNode = pQ.front();
        pQ.pop();
        --size;

        // Change that node has children from false to true also increase the total number of expanded nodes
        if (frontNode->children == false) {
            frontNode->children = true;
            ++expanded;
        }

        // If goal is achieved print goal statement and exit general search function
        if (goal == frontNode->puzzle) {
            goalStatement(expanded, maxSize, frontNode, pSize);
            // To exit function once finished so that the program will end
            return;
        }

        // Print current node with its g(n) and h(n)
        stateStatement(expanded, frontNode, pSize);

        // Expand node
        Node* expandFunc = expand(frontNode, pS);
        Node* child[] = {expandFunc->childLeft, expandFunc->childRight, expandFunc->childUp, expandFunc->childDown};

        // Assign heuristics to expanded nodes
        for (unsigned i = 0; i < 4; ++i) {
            if (child[i] != nullptr) {
                if (func == 1) {
                    // Uniform Cost Search Heuristic
                    child[i]->cost = 0;
                    child[i]->depth = frontNode->depth + 1;
                } else if (func == 2) {
                    // Misplaced Tile Heuristic
                    child[i]->cost = misplacedHeuristic(child[i]->puzzle);
                    child[i]->depth = frontNode->depth + 1;
                } else if (func == 3) {
                    // Manhattan Distance Heuristic
                    child[i]->cost = manhattanHeuristic(child[i]->puzzle);
                    child[i]->depth = frontNode->depth + 1;
                }
                // Push child to queue of nodes
                pQ.push(child[i]);

                // Insert child puzzle into set of already expanded nodes
                pS.insert(child[i]->puzzle);

                // Increase size of queue
                ++size;
            }
        }

        // Increase max size if the queue size has surpassed the maxSize variable value
        maxSize = fmax(pQ.size(), maxSize);
    }

    // If the queue size is equal to 0 then the algorithm has failed
    if (pQ.size() == 0) {
        cout << endl << "Failure!" << endl << endl;
    }

    return;
}

// Referenced example code given for outputs
int main() {
    int puzzleType = 0; // Default or DIY
    int algorithmChoice = 0; // UCS, Misplaced, or Manhattan
    vector<vector<int>> puzzle; // 8 puzzle 2d vector
    vector<int> row; // Vector rows for 2d vector initialization
    int pSize = 3; // 3x3 puzzle, can be changed to make a size x size puzzle
    int diff = 0; // Default difficulty
    int num = 0; // Read in DIY values

    // Initializes vector so it can be filled
    for (unsigned i = 0; i < pSize; ++i) {
        for (unsigned j = 0; j < pSize; ++j) {
            row.push_back(0);
        }
        puzzle.push_back(row);
        row.clear();
    }

    // Start of puzzle solver
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

        for (unsigned i = 0; i < pSize; ++i) {
            cout << "Enter row " << i + 1 << ", use space or tabs between numbers" << endl;
            for (unsigned j = 0; j < pSize; ++j) {
                cin >> num;
                puzzle.at(i).at(j) = num;
            }
        }
        cout << "Your puzzle:" << endl;
    }

    // Outputs puzzle to be solved to console
    for (unsigned i = 0; i < pSize; ++i) {
        for (unsigned j = 0; j < pSize; ++j) {
            cout << puzzle[i][j];

            if (j < pSize - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << endl;

    cout << "Enter your choice of algorithm" << endl
         << "  1. Uniform Cost Search" << endl
         << "  2. A* with the Misplaced Tile heuristic" << endl
         << "  3. A* with the Manhattan distance heuristic" << endl;

    cin >> algorithmChoice;

    cout << endl;

    // Timer for timing how long the algorithm takes to solve the puzzle
    auto start = chrono::steady_clock::now();

    // Running the algorithm
    generalSearch(puzzle, algorithmChoice, pSize);

    auto end = chrono::steady_clock::now();

    cout << "CPU time in nanoseconds: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << " ns" << endl;

    cout << "CPU time in microseconds: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs" << endl;

    cout << "CPU time in seconds: "
         << chrono::duration_cast<chrono::seconds>(end - start).count()
         << " secs" << endl;

    cout << "CPU time in minutes: "
         << chrono::duration_cast<chrono::minutes>(end - start).count()
         << " mins" << endl;

    return 0;
}