//
// Created by Cristina Lawson on 2/17/21.
//

#include <iostream>

#ifndef EIGHT_PUZZLE_TREE_H
#define EIGHT_PUZZLE_TREE_H

#include "Node.h"
using namespace std;

class Tree {

private:
    Node *root;

private:
    void preOrder(Node *) const;
    void inOrder(Node *) const;
    void postOrder(Node *) const;
    void remove(Node *, Node*, int);
    Node * search(const int &, Node *) const;
    Node * min(Node *curr)const;
    Node * max(Node *curr)const;

public:
    Tree();
    void insert(const int &);
    bool search(const int &) const;
    void inOrder() const;
    void postOrder() const;
    void preOrder() const;
    int largest() const;
    int smallest() const;
    int height(const int &) const;
    void remove(const int &);
};

#endif //EIGHT_PUZZLE_TREE_H
