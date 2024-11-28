#ifndef BPTREE_H
#define BPTREE_H

#include <vector>
#include <memory>
#include <algorithm>

template <typename KeyType, typename ValueType>
class BPTreeNode {
public:
    bool is_leaf;
    std::vector<KeyType> keys;
    std::vector<std::shared_ptr<BPTreeNode>> children;
    std::vector<ValueType> values;
    std::shared_ptr<BPTreeNode> next;

    BPTreeNode(bool leaf) : is_leaf(leaf), next(nullptr) {}
};

template <typename KeyType, typename ValueType>
class BPTree {
private:
    std::shared_ptr<BPTreeNode<KeyType, ValueType>> root;
    int min_degree;

    void insert_internal(const KeyType& key, const ValueType& value, std::shared_ptr<BPTreeNode<KeyType, ValueType>> node);
    void split_child(std::shared_ptr<BPTreeNode<KeyType, ValueType>> parent, int index);

public:
    BPTree(int degree) : root(std::make_shared<BPTreeNode<KeyType, ValueType>>(true)), min_degree(degree) {}

    void insert(const KeyType& key, const ValueType& value);
    std::vector<ValueType> search(const KeyType& key);
};

#include "bptree_impl.h"

#endif // BPTREE_H