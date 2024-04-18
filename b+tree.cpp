//
// Created by yjwan on 4/16/2024.
//
#include "b+tree.h"



void BPlusTree::insert(House house) {
    // If the tree is empty, create a new root
    if (root == nullptr) {
        root = new Node();
        root->houses.push_back(house);
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    // Find the appropriate leaf node
    while (!current->leaf) {
        parent = current;
        int i = 0;
        while (i < current->houses.size() && house.house_price > current->houses[i].house_price) {
            i++;
        }
        current = current->children[i];
    }

    // Insert the new house into the leaf node
    current->houses.push_back(house);

    // If the leaf node overflows, split it
    if (current->houses.size() > degree - 1) {
        Node* new_leaf = new Node();
        int split_point = degree / 2;

        // Move the second half of houses to the new leaf node
        new_leaf->houses.assign(current->houses.begin() + split_point, current->houses.end());
        current->houses.erase(current->houses.begin() + split_point, current->houses.end());

        // Adjust pointers
        if (parent == nullptr) {
            parent = new Node();
            root = parent;
            parent->children.push_back(current);
        }
        int i = 0;
        while (i < parent->houses.size() && parent->houses[i].house_price < new_leaf->houses[0].house_price) {
            i++;
        }
        parent->houses.insert(parent->houses.begin() + i, new_leaf->houses[0]);
        parent->children.insert(parent->children.begin() + i + 1, new_leaf);
    }
}