#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <vector>
#include <memory>

// Forward declaration
template <typename Key, typename Value>
class BPlusTree;

template <typename Key, typename Value>
class BPlusTreeNode {
public:
    bool isLeaf;
    std::vector<Key> keys;
    std::vector<std::shared_ptr<BPlusTreeNode>> children;
    std::vector<Value> values;
    std::shared_ptr<BPlusTreeNode> next;

    BPlusTreeNode(bool leaf);
};

template <typename Key, typename Value>
class BPlusTree {
public:
    BPlusTree(int degree);
    void insert(const Key& key, const Value& value);
    void remove(const Key& key);
    bool search(const Key& key, Value& value) const;

private:
    std::shared_ptr<BPlusTreeNode<Key, Value>> root;
    int degree;
    void insertInternal(const Key& key, const Value& value, std::shared_ptr<BPlusTreeNode<Key, Value>> node, std::shared_ptr<BPlusTreeNode<Key, Value>> parent);
    void splitChild(std::shared_ptr<BPlusTreeNode<Key, Value>> node, int index);
    void mergeChild(std::shared_ptr<BPlusTreeNode<Key, Value>> node, int index);
    void removeInternal(const Key& key, std::shared_ptr<BPlusTreeNode<Key, Value>> node);
    bool searchInternal(const Key& key, Value& value, std::shared_ptr<BPlusTreeNode<Key, Value>> node) const;
};

#include "bplustree.cpp"

#endif // BPLUSTREE_H