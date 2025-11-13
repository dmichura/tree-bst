#ifndef BST_H
#define BST_H

#include <string>
#include <fstream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;
public:
    BST();
    ~BST();
};

#endif