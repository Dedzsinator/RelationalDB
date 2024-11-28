#ifndef BPTREE_IMPL_H
#define BPTREE_IMPL_H

#include "bptree.h"

template <typename KeyType, typename ValueType>
void BPTree<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    if (root->keys.size() == 2 * min_degree - 1) {
        auto new_root = std::make_shared<BPTreeNode<KeyType, ValueType>>(false);
        new_root->children.push_back(root);
        split_child(new_root, 0);
        root = new_root;
    }
    insert_internal(key, value, root);
}

template <typename KeyType, typename ValueType>
void BPTree<KeyType, ValueType>::insert_internal(const KeyType& key, const ValueType& value, std::shared_ptr<BPTreeNode<KeyType, ValueType>> node) {
    if (node->is_leaf) {
        auto it = std::lower_bound(node->keys.begin(), node->keys.end(), key);
        node->keys.insert(it, key);
        node->values.insert(node->values.begin() + (it - node->keys.begin()), value);
    } else {
        auto it = std::upper_bound(node->keys.begin(), node->keys.end(), key);
        int index = it - node->keys.begin();
        if (node->children[index]->keys.size() == 2 * min_degree - 1) {
            split_child(node, index);
            if (key > node->keys[index]) {
                index++;
            }
        }
        insert_internal(key, value, node->children[index]);
    }
}

template <typename KeyType, typename ValueType>
void BPTree<KeyType, ValueType>::split_child(std::shared_ptr<BPTreeNode<KeyType, ValueType>> parent, int index) {
    auto node = parent->children[index];
    auto new_node = std::make_shared<BPTreeNode<KeyType, ValueType>>(node->is_leaf);
    parent->keys.insert(parent->keys.begin() + index, node->keys[min_degree - 1]);
    parent->children.insert(parent->children.begin() + index + 1, new_node);

    new_node->keys.assign(node->keys.begin() + min_degree, node->keys.end());
    node->keys.resize(min_degree - 1);

    if (node->is_leaf) {
        new_node->values.assign(node->values.begin() + min_degree, node->values.end());
        node->values.resize(min_degree);
        new_node->next = node->next;
        node->next = new_node;
    } else {
        new_node->children.assign(node->children.begin() + min_degree, node->children.end());
        node->children.resize(min_degree);
    }
}

template <typename KeyType, typename ValueType>
std::vector<ValueType> BPTree<KeyType, ValueType>::search(const KeyType& key) {
    auto node = root;
    while (!node->is_leaf) {
        auto it = std::upper_bound(node->keys.begin(), node->keys.end(), key);
        node = node->children[it - node->keys.begin()];
    }
    std::vector<ValueType> result;
    auto it = std::lower_bound(node->keys.begin(), node->keys.end(), key);
    while (it != node->keys.end() && *it == key) {
        result.push_back(node->values[it - node->keys.begin()]);
        it++;
    }
    return result;
}

#endif // BPTREE_IMPL_H