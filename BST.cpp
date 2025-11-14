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

void BST::remove(int value) {
    if (root == nullptr) {
        std::cout << "Drzewo jest puste. Nie mozna usunac.\n";
        return;
    }
    root = removeRecursive(root, value);
}


Node* BST::removeRecursive(Node* node, int value) {

    if (node == nullptr) {
        std::cout << "Element " << value << " nie istnieje w drzewie.\n";
        return nullptr;
    }


    if (value < node->data) {
        node->left = removeRecursive(node->left, value);
    } else if (value > node->data) {
        node->right = removeRecursive(node->right, value);
    } 

    else {

        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            std::cout << "Usunieto lisc " << value << ".\n";
            return nullptr;
        }
        

        
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            std::cout << "Usunieto " << value << " (mial jedno dziecko).\n";
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            std::cout << "Usunieto " << value << " (mial jedno dziecko).\n";
            return temp;
        }

        Node* successor = findMin(node->right);
        node->data = successor->data;
        std::cout << "Usunieto " << value << " (mial dwoje dzieci, zastapiono przez " << successor->data << ").\n";
        node->right = removeRecursive(node->right, successor->data);
    }
    return node;
}

Node* BST::findMin(Node* node) {
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void BST::add(int value) {
    root = addRecursive(root, value);
}


Node* BST::addRecursive(Node* node, int value) {

    if (node == nullptr) {
        return new Node(value);
    }


    if (value < node->data) {
        node->left = addRecursive(node->left, value);
    } else if (value > node->data) {
        node->right = addRecursive(node->right, value);
    }

    else {
        std::cout << "Element " << value << " juz istnieje. Pomijam.\n";
    }

    return node;
}

#endif