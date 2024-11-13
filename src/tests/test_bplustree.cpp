#include "bplustree.h"
#include <iostream>
#include <cassert>

void testBPlusTree() {
    BPlusTree<int, std::string> tree(3);

    // Test insert
    tree.insert(1, "Alice");
    tree.insert(2, "Bob");
    tree.insert(3, "Charlie");

    // Test search
    std::string value;
    assert(tree.search(1, value) && value == "Alice");
    assert(tree.search(2, value) && value == "Bob");
    assert(tree.search(3, value) && value == "Charlie");

    // Test remove
    tree.remove(2);
    assert(!tree.search(2, value));

    std::cout << "BPlusTree tests passed.\n";
}

int main() {
    testBPlusTree();
    return 0;
}