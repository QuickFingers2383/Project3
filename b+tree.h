//
// Created by yjwan on 4/16/2024.
//

#ifndef PROJECT3_B_TREE_H
#define PROJECT3_B_TREE_H

#include <iostream>
#include <vector>
#include "House.h"

using namespace std;

// Tree node
struct Node {
    vector<House> houses; // Stores houses
    vector<Node*> children; // Stores pointers to child nodes
    bool leaf; // Indicates if the node is a leaf
    Node() : leaf(true) {}
};

// B+ tree clas
class BPlusTree {
private:
    Node* root;
    int degree; // Degree of the B+ tree
public:
    BPlusTree(int degree) : root(nullptr), degree(degree) {}
    void Insert(House house, string type);
    House* Search(float key, string type);
    void remove(int key);
    void handleUnderflow(Node* current, Node* parent);
};

#endif //PROJECT3_B_TREE_H