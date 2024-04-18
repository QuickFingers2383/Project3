#include <iostream>
#include "b+tree.h"

int main() {
    // Create a B+ tree with degree 3
    BPlusTree bptree(3);

    // Insert housing data into the B+ tree
    House house1 = {250000, 2000, 2,  2.5,   2005};
    House house2 = {320000, 2200, 1,  2.5,  2010};
    // Insert more houses as needed

    bptree.insert(house1);
    bptree.insert(house2);
    // Insert more houses as needed

    // Search for a house based on certain criteria
    House searched_house = bptree.search(320000);
    // Print the searched house attributes

    // Remove a house from the B+ tree
    bptree.remove(250000);

    return 0;
}
