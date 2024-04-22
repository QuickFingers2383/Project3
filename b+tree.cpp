//
// Created by yjwan on 4/16/2024.
//
#include "b+tree.h"
#include <iostream>
#include <vector>

void BPlusTree::Insert(House house, string type) {
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
        if(type == "price") {
            while (i < current->houses.size() && house.house_price > current->houses[i].house_price) {
                i++;
            }
        } else if(type == "square_feet") {
            while (i < current->houses.size() && house.square_feet > current->houses[i].square_feet) {
                i++;
            }
        } else if(type == "bedrooms") {
            while (i < current->houses.size() && house.bedrooms > current->houses[i].bedrooms) {
                i++;
            }
        } else if(type == "bathrooms") {
            while (i < current->houses.size() && house.bathrooms > current->houses[i].bathrooms) {
                i++;
            }
        } else if(type == "year") {
            while (i < current->houses.size() && house.year_built > current->houses[i].year_built) {
                i++;
            }
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

        // Adjust pointers and set leaf flags
        new_leaf->leaf = true; // Set leaf flag for the new leaf node
        if (parent == nullptr) {
            parent = new Node();
            root = parent;
            parent->children.push_back(current);
        }
        int i = 0;
        if(type == "price") {
            while (i < parent->houses.size() && parent->houses[i].house_price < new_leaf->houses[0].house_price) {
                i++;
            }
        } else if (type == "square_feet") {
            while (i < parent->houses.size() && parent->houses[i].square_feet < new_leaf->houses[0].square_feet) {
                i++;
            }
        } else if (type == "bedrooms") {
            while (i < parent->houses.size() && parent->houses[i].bedrooms < new_leaf->houses[0].bedrooms) {
                i++;
            }
        } else if (type == "bathrooms") {
            while (i < parent->houses.size() && parent->houses[i].bathrooms < new_leaf->houses[0].bathrooms) {
                i++;
            }
        } else if (type == "year") {
            while (i < parent->houses.size() && parent->houses[i].year_built < new_leaf->houses[0].year_built) {
                i++;
            }
        }
        parent->houses.insert(parent->houses.begin() + i, new_leaf->houses[0]);
        parent->children.insert(parent->children.begin() + i + 1, new_leaf);

        // Adjust leaf flag for the parent
        parent->leaf = false;
    }
}

void BPlusTree::display(House house) {
    cout << "Price: " << house.house_price <<
    "\nArea: " << house.square_feet <<
    "\nNumber of bedrooms: " << house.bedrooms <<
    "\nNumber of bathrooms: " << house.bathrooms <<
    "\nYear built: " << house.year_built <<
    "\n" << endl;
}

//searches for house in b+ tree, returns pointer if found
House* BPlusTree::Search(float key, const string& type) {

    if (root == nullptr) {
        return nullptr;
    }

    Node* current = root;

    while (!current->leaf) {
        int i = 0;
        //navigates to the correct node, similar to insert
        if(type == "price") {
            while (i < current->houses.size() && key >= current->houses[i].house_price) {
                i++;
            }
        } else if(type == "square_feet") {
            while (i < current->houses.size() && key >= current->houses[i].square_feet) {
                i++;
            }
        } else if(type == "bedrooms") {
            while (i < current->houses.size() && key >= current->houses[i].bedrooms) {
                i++;
            }
        } else if(type == "bathrooms") {
            while (i < current->houses.size() && key >= current->houses[i].bathrooms) {
                i++;
            }
        } else if(type == "year") {
            while (i < current->houses.size() && key >= current->houses[i].year_built) {
                i++;
            }
        }
        current = current->children[i];
    }

    for (auto &house : current->houses) {
        if(type == "price") {
            if (house.house_price == key) {
                return &house; // returns a pointer to the house if found
            }
        } else if(type == "square_feet") {
            if (house.square_feet == key) {
                return &house; // returns a pointer to the house if found
            }
        } else if(type == "bedrooms") {
            if (house.bedrooms == key) {
                return &house; // returns a pointer to the house if found
            }
        } else if(type == "bathrooms") {
            if (house.bathrooms == key) {
                return &house; // returns a pointer to the house if found
            }
        } else if(type == "year") {
            if (house.year_built == key) {
                return &house; // returns a pointer to the house if found
            }
        }
    }
    return nullptr; // house with the exact price not found
}


//removes from B+ tree
//void BPlusTree::remove(int price) {
//    if (root == nullptr) {
//        return; //checks if empty, nothing to remove
//    }
//
//    Node* current = root;
//    Node* parent = nullptr;
//    bool found = false;
//
//    while (!current->leaf) {
//        parent = current;
//        int i = 0;
//        while (i < current->houses.size() && price >= current->houses[i].house_price) {
//            if (price == current->houses[i].house_price) found = true;
//            i++;
//        }
//        current = current->children[i];
//    }
//
//    // remove house if found
//    if (found) {
//        auto it = std::remove_if(current->houses.begin(), current->houses.end(),
//                                 [price](const House& house) { return house.house_price == price; });
//        current->houses.erase(it, current->houses.end());
//
//    //check if underflows which may cause a problem
//        if (current->houses.size() < (degree - 1) / 2) {
//            handleUnderflow(current, parent);
//        }
//    }
//}
//
//void BPlusTree::handleUnderflow(Node* current, Node* parent) {
//    int childIndex = std::find(parent->children.begin(), parent->children.end(), current) - parent->children.begin();
//
//    // Try to borrow from the left sibling if possible
//    if (childIndex > 0 && parent->children[childIndex - 1]->houses.size() > (degree - 1) / 2) {
//        Node* leftSibling = parent->children[childIndex - 1];
//        current->houses.insert(current->houses.begin(), leftSibling->houses.back());
//        leftSibling->houses.pop_back();
//        parent->houses[childIndex - 1] = current->houses.front();
//    }
//    // Try to borrow from the right sibling if possible
//    else if (childIndex < parent->children.size() - 1 && parent->children[childIndex + 1]->houses.size() > (degree - 1) / 2) {
//        Node* rightSibling = parent->children[childIndex + 1];
//        current->houses.push_back(rightSibling->houses.front());
//        rightSibling->houses.erase(rightSibling->houses.begin());
//        parent->houses[childIndex] = rightSibling->houses.front();
//    }
//    // otherwise merge
//    else {
//        if (childIndex > 0) {
//            // merge with left sibling
//            Node* leftSibling = parent->children[childIndex - 1];
//            leftSibling->houses.insert(leftSibling->houses.end(), current->houses.begin(), current->houses.end());
//            parent->houses.erase(parent->houses.begin() + childIndex - 1);
//            parent->children.erase(parent->children.begin() + childIndex);
//            delete current;
//        } else {
//            // merge with right sibling
//            Node* rightSibling = parent->children[childIndex + 1];
//            current->houses.insert(current->houses.end(), rightSibling->houses.begin(), rightSibling->houses.end());
//            parent->houses.erase(parent->houses.begin() + childIndex);
//            parent->children.erase(parent->children.begin() + childIndex + 1);
//            delete rightSibling;
//        }
//    }
//
//    // if root is empty change with root
//    if (parent == root && parent->houses.empty()) {
//        if (parent->children.empty()) {
//            delete root;
//            root = nullptr;
//        } else {
//            Node* newRoot = parent->children[0];
//            delete root;
//            root = newRoot;
//        }
//    }
//}

