#ifndef BST_CPP
#define BST_CPP

#include "BST.h"
#include <iostream>

using namespace std;

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

bool BST::isEmpty() {
    return root == nullptr;
}

void BST::remove(int value) {
    if (root == nullptr) {
        cout << "Drzewo jest puste. Nie mozna usunac\n";
        return;
    }
    root = removeRecursive(root, value);
}


Node* BST::removeRecursive(Node* node, int value) {

    if (node == nullptr) {
        cout << "Element " << value << " nie istnieje w drzewie\n";
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
            cout << "Usunieto lisc " << value << ".\n";
            return nullptr;
        }
        

        
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            cout << "Usunieto " << value << " (mial jedno dziecko).\n";
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            cout << "Usunieto " << value << " (mial jedno dziecko).\n";
            return temp;
        }

        Node* successor = findMin(node->right);
        node->data = successor->data;
        cout << "Usunieto " << value << " (mial dwoje dzieci, zastapiono przez " << successor->data << ").\n";
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

    return node;
}

void BST::loadFromFile(const string& filename) {

    ifstream inFile(filename, ios::binary);
    if (!inFile.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku " << filename << " do odczytu\n";
        return;
    }


    clear(); 
    int value;
    
    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        add(value);
    }

    if (inFile.eof()) {
        cout << "Pomyslnie wczytano drzewo z pliku " << filename << "\n";
    } else if (inFile.fail()) {
        cout << "Blad podczas odczytu danych z pliku (niepoprawny format?)\n";
    }
    
    inFile.close();
}

void BST::saveRecursive(Node* node, ofstream& outFile) {
    if (node == nullptr) {
        return;
    }

    outFile.write(reinterpret_cast<const char*>(&node->data), sizeof(int));
    

    saveRecursive(node->left, outFile);
    saveRecursive(node->right, outFile);
}

void BST::saveToFile(const string& filename) {
    ofstream outFile(filename, ios::binary); 
    if (!outFile.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku " << filename << " do zapisu.\n";
        return;
    }

    if (isEmpty()) {
        cout << "Drzewo jest puste. Zapisano pusty plik.\n";
        outFile.close();
        return;
    }

    saveRecursive(root, outFile);
    outFile.close();
    cout << "Drzewo zostalo zapisane binarnie do pliku " << filename << ".\n";
}

void BST::displayInorder() {
    cout << "In-order (LKP):  ";
    if (isEmpty()) cout << "[PUSTE]";
    inorderRecursive(root);
    cout << "\n";
}

void BST::inorderRecursive(Node* node) {
    if (node == nullptr) return;
    inorderRecursive(node->left);
    cout << node->data << " ";
    inorderRecursive(node->right);
}

void BST::displayPreorder() {
    cout << "Pre-order (KLP): ";
    if (isEmpty()) cout << "[PUSTE]";
    preorderRecursive(root);
    cout << "\n";
}

void BST::preorderRecursive(Node* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    preorderRecursive(node->left);
    preorderRecursive(node->right);
}

void BST::displayPostorder() {
    cout << "Post-order (LPK):";
    if (isEmpty()) cout << "[PUSTE]";
    postorderRecursive(root);
    cout << "\n";
}

void BST::postorderRecursive(Node* node) {
    if (node == nullptr) return;
    postorderRecursive(node->left);
    postorderRecursive(node->right);
    cout << node->data << " ";
}

#endif