#ifndef BST_H
#define BST_H

#include <string>
#include <fstream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    void clearRecursive(Node* node);
public:
    BST();
    ~BST();

    void clear();
    bool isEmpty();

    void add(int value); 
    void remove(int value); 

    void displayInorder();
    void displayPreorder();
    void displayPostorder();
    void displayGraphical();

    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
};

#endif