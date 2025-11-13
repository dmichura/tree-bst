#ifndef BST_CPP
#define BST_CPP

#include "BST.h"
#include <iostream>

BST::BST() : root(nullptr) {}

BST::~BST() {
}

void BST::clearRecursive(Node* node) {
    if (node == nullptr) {
        return;
    }
    clearRecursive(node->left);
    clearRecursive(node->right);
    delete node;
}

void BST::clear() {
    clearRecursive(root);
    root = nullptr;
}

#endif