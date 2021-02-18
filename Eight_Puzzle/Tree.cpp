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
        cout << curr->data << "(" << curr->count << "), ";
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void Tree::inOrder(Node *curr) const {
    if (curr != nullptr) {
        inOrder(curr->left);
        cout << curr->data << "(" << curr->count << "), ";
        inOrder(curr->right);
    }
}

void Tree::postOrder(Node *curr) const {
    if (curr != nullptr) {
        postOrder(curr->left);
        postOrder(curr->right);
        cout << curr->data << "(" << curr->count << "), ";
    }
}

void Tree::remove(Node *prev, Node* curr, string data) {

    if (curr == nullptr) {
        return;
    }
    else if(curr->data == data){
        if(curr->count > 1 && curr->data != prev->data){
            curr->count = curr->count - 1;
            return;
        }
        if(curr == root && curr->count > 1){
            curr->count = curr->count - 1;
            return;
        }
        else if(!curr->right && !curr->left) {

            if(curr->data > prev->data) {
                prev->right = nullptr;
                delete curr;
                return;
            }
            else if(curr->data < prev->data) {
                prev->left = nullptr;
                delete curr;
                return;
            }
            else if(curr->data == prev->data) {
                if(prev->right == nullptr){
                    prev->left = nullptr;
                    delete curr;
                }
                else if(prev->left == nullptr) {
                    prev->right = nullptr;
                    delete curr;
                }
                else if(prev->right && prev->left){
                    if(curr->data == prev->left->data){
                        prev->left = nullptr;
                        delete curr;
                    }
                    else if(curr->data == prev->right->data){
                        prev->right = nullptr;
                        delete curr;
                    }
                }
            }
        }
        else if((curr->left != nullptr && curr->right != nullptr) || (curr->left != nullptr && curr->right == nullptr)){
            Node* temp = max(curr->left);
            curr->data = temp->data;
            curr->count = temp->count;
            remove(curr, curr->left, curr->data);
        }
        else if(!curr->left && curr->right){
            Node *temp = min(curr->right);
            curr->data = temp->data;
            curr->count = temp->count;
            remove(curr, curr-> right, curr->data);
        }
    }
    else if(curr->data < data){
        remove(curr, curr->right, data);
    }
    else if (curr->data > data) {
        remove(curr, curr->left, data);
    }
}

Node * Tree::search(const string &data, Node *curr) const {
    if (curr != nullptr) {
        if (data == curr->data) {
            return curr;
        }
        else {
            if (data < curr->data) {
                return search(data, curr->left);
            }
            else {
                return search(data, curr->right);
            }
        }
    }
    else {
        return nullptr;
    }
}

void Tree::insert(const int &data) {
    Node* curr = root;
    Node* newN = nullptr;

    if (search(data)) {
        curr = search(data, root);
        curr->count = curr->count + 1;
    }
    else {
        newN = new Node(data);

        if (root == nullptr) {
            root = newN;
        }
        else {
            while (1) {
                if (data < curr->data) {
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

bool Tree::search(const string &data) const {
    return search(data, root);
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

string Tree::largest() const {
    Node* curr = root;

    if (curr == nullptr) {
        return "";
    }
    else {
        while(1) {
            if (curr->right == nullptr) {
                return curr->data;
            }
            else {
                curr = curr->right;
            }
        }
    }
}

string Tree::smallest() const {
    Node* curr = root;

    if (curr == nullptr) {
        return "";
    }
    else {
        while(1) {
            if (curr->left == nullptr) {
                return curr->data;
            }
            else {
                curr = curr->left;
            }
        }
    }

}

int Tree::height(const string &data) const {

    if (!search(data)) {
        return -1;
    }

    Node* curr = search(data, root);
    Node* currL = curr;
    Node* currR = curr;
    int countL = 0;
    int countR = 0;

    if (curr->left != nullptr) {
        currL = currL->left;
        countL++;
        countL = countL + height(currL->data);
    }

    if (curr->right != nullptr) {
        currR = currR->right;
        countR++;
        countR = countR + height(currR->data);
    }

    if (countL >= countR) {
        return countL;
    }
    else {
        return countR;
    }
}

void Tree::remove(const string &data) {

    if (root == nullptr) {
        return;
    }
    else if ((!root->right && !root->left) && (root->data == data)) {
        delete root;
        root = nullptr;
        return;
    }
    remove(root, root, data);
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
