//
// Created by Cristina Lawson on 2/17/21.
//

#include "Tree.h"

#include <iostream>
using namespace std;

Tree::Tree() {
    root = nullptr;
}

void Tree::preOrder(Node *curr) const {
    if (curr != nullptr) {
        cout << curr->cost << "(" << curr->depth << "), ";
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void Tree::inOrder(Node *curr) const {
    if (curr != nullptr) {
        inOrder(curr->left);
        cout << curr->cost << "(" << curr->depth << "), ";
        inOrder(curr->right);
    }
}

void Tree::postOrder(Node *curr) const {
    if (curr != nullptr) {
        postOrder(curr->left);
        postOrder(curr->right);
        cout << curr->cost << "(" << curr->depth << "), ";
    }
}

void Tree::remove(Node *prev, Node* curr, int cost) {

    if (curr == nullptr) {
        return;
    }
    else if(curr->cost == cost){
        if(curr->depth > 1 && curr->cost != prev->cost){
            curr->depth = curr->depth - 1;
            return;
        }
        if(curr == root && curr->depth > 1){
            curr->depth = curr->depth - 1;
            return;
        }
        else if(!curr->right && !curr->left) {

            if(curr->cost > prev->cost) {
                prev->right = nullptr;
                delete curr;
                return;
            }
            else if(curr->cost < prev->cost) {
                prev->left = nullptr;
                delete curr;
                return;
            }
            else if(curr->cost == prev->cost) {
                if(prev->right == nullptr){
                    prev->left = nullptr;
                    delete curr;
                }
                else if(prev->left == nullptr) {
                    prev->right = nullptr;
                    delete curr;
                }
                else if(prev->right && prev->left){
                    if(curr->cost == prev->left->cost){
                        prev->left = nullptr;
                        delete curr;
                    }
                    else if(curr->cost == prev->right->cost){
                        prev->right = nullptr;
                        delete curr;
                    }
                }
            }
        }
        else if((curr->left != nullptr && curr->right != nullptr) || (curr->left != nullptr && curr->right == nullptr)){
            Node* temp = max(curr->left);
            curr->cost = temp->cost;
            curr->depth = temp->depth;
            remove(curr, curr->left, curr->cost);
        }
        else if(!curr->left && curr->right){
            Node *temp = min(curr->right);
            curr->cost = temp->cost;
            curr->depth = temp->depth;
            remove(curr, curr-> right, curr->cost);
        }
    }
    else if(curr->cost < cost){
        remove(curr, curr->right, cost);
    }
    else if (curr->cost > cost) {
        remove(curr, curr->left, cost);
    }
}

Node * Tree::search(const int &cost, Node *curr) const {
    if (curr != nullptr) {
        if (cost == curr->cost) {
            return curr;
        }
        else {
            if (cost < curr->cost) {
                return search(cost, curr->left);
            }
            else {
                return search(cost, curr->right);
            }
        }
    }
    else {
        return nullptr;
    }
}

void Tree::insert(const int &cost) {
    Node* curr = root;
    Node* newN = nullptr;

    if (search(cost)) {
        curr = search(cost, root);
        curr->depth = curr->depth + 1;
    }
    else {
        newN = new Node(cost);

        if (root == nullptr) {
            root = newN;
        }
        else {
            while (1) {
                if (cost < curr->cost) {
                    if (curr->left == nullptr) {
                        curr->left = newN;
                        newN->parent = curr;
                        return;
                    }
                    else {
                        curr = curr->left;
                    }
                }
                else if (curr->right == nullptr) {
                    curr->right = newN;
                    newN->parent = curr;
                    return;
                }
                else {
                    curr = curr->right;
                }
            }
        }
    }
}

bool Tree::search(const int &cost) const {
    return search(cost, root);
}

void Tree::inOrder() const {
    inOrder(root);
    cout << endl;
}

void Tree::postOrder() const {
    postOrder(root);
    cout << endl;
}

void Tree::preOrder() const {
    preOrder(root);
    cout << endl;
}

int Tree::largest() const {
    Node* curr = root;

    if (curr == nullptr) {
        return 0;
    }
    else {
        while(1) {
            if (curr->right == nullptr) {
                return curr->cost;
            }
            else {
                curr = curr->right;
            }
        }
    }
}

int Tree::smallest() const {
    Node* curr = root;

    if (curr == nullptr) {
        return 0;
    }
    else {
        while(1) {
            if (curr->left == nullptr) {
                return curr->cost;
            }
            else {
                curr = curr->left;
            }
        }
    }

}

int Tree::height(const int &cost) const {

    if (!search(cost)) {
        return -1;
    }

    Node* curr = search(cost, root);
    Node* currL = curr;
    Node* currR = curr;
    int countL = 0;
    int countR = 0;

    if (curr->left != nullptr) {
        currL = currL->left;
        countL++;
        countL = countL + height(currL->cost);
    }

    if (curr->right != nullptr) {
        currR = currR->right;
        countR++;
        countR = countR + height(currR->cost);
    }

    if (countL >= countR) {
        return countL;
    }
    else {
        return countR;
    }
}

void Tree::remove(const int &cost) {

    if (root == nullptr) {
        return;
    }
    else if ((!root->right && !root->left) && (root->cost == cost)) {
        delete root;
        root = nullptr;
        return;
    }
    remove(root, root, cost);
}

Node * Tree::min(Node *curr)const {
    Node *temp = curr;

    while(curr != nullptr){
        temp = curr;
        curr = curr->left;
    }

    return temp;
}

Node * Tree::max(Node *curr)const {
    Node *temp = curr;

    while(curr != nullptr){
        temp = curr;
        curr = curr->right;
    }
    return temp;
}
