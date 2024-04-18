#include <iostream>
#include "b+tree.h"

int main() {
    // Create a B+ tree with degree 3
    BPlusTree bptree(3);

    // testing
    House house1 = {250000, 2000, 2,  2.5,   2005};
    House house2 = {320000, 2200, 1,  2.5,  2010};

    bptree.insert(house1);
    bptree.insert(house2);

    return 0;
}
