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
    void remove(Node *, Node*, string);
    Node * search(const string &, Node *) const;
    Node * min(Node *curr)const;
    Node * max(Node *curr)const;

public:
    Tree();
    void insert(const int &);
    bool search(const string &) const;
    void inOrder() const;
    void postOrder() const;
    void preOrder() const;
    string largest() const;
    string smallest() const;
    int height(const string &) const;
    void remove(const string &);
};

#endif //EIGHT_PUZZLE_TREE_H
