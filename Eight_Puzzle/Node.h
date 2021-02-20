//
// Created by Cristina Lawson on 2/17/21.
//

#ifndef EIGHT_PUZZLE_NODE_H
#define EIGHT_PUZZLE_NODE_H

#include <iostream>
#include <vector>

using namespace std;

class Node {

public:
    vector<vector<int>> puzzle;
    int cost;
    int depth;
    Node* childLeft;
    Node* childRight;
    Node* childUp;
    Node* childDown;
    bool children;

    Node(vector<vector<int>> puzzle):puzzle(puzzle), cost(0), depth(0), childLeft(0), childRight(0), childUp(0), childDown(), children(false){}
};


#endif //EIGHT_PUZZLE_NODE_H
