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
    Node* removeRecursive(Node* node, int value);
    Node* findMin(Node* node);
    Node* addRecursive(Node* node, int value);
    
    void saveRecursive(Node* node, ofstream& outFile);
    void clearRecursive(Node* node);

    void inorderRecursive(Node* node);
    void preorderRecursive(Node* node);
    void postorderRecursive(Node* node);
    void displayGraphicalRecursive(Node* node, const string& prefix, bool isLeft, bool isRoot);
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