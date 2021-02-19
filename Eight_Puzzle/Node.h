//
// Created by Cristina Lawson on 2/17/21.
//

#ifndef EIGHT_PUZZLE_NODE_H
#define EIGHT_PUZZLE_NODE_H

#include <iostream>
#include <vector>

using namespace std;

class Node {
    friend class Tree;

private:
    int cost;
    int depth;
    Node* left;
    Node* right;
    Node* parent;

public:
    Node(int cost):cost(cost), puzzle(0), depth(0), left(0),right(0), parent(0){}
    vector<vector<int>> puzzle;
};


#endif //EIGHT_PUZZLE_NODE_H
