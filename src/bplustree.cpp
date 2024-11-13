#include "bplustree.h"
#include <algorithm>

template <typename Key, typename Value>
BPlusTreeNode<Key, Value>::BPlusTreeNode(bool leaf) : isLeaf(leaf), next(nullptr) {}

template <typename Key, typename Value>
BPlusTree<Key, Value>::BPlusTree(int degree) : degree(degree), root(std::make_shared<BPlusTreeNode<Key, Value>>(true)) {}

template <typename Key, typename Value>
void BPlusTree<Key, Value>::insert(const Key& key, const Value& value) {
    if (root->keys.size() == 2 * degree - 1) {
        auto newRoot = std::make_shared<BPlusTreeNode<Key, Value>>(false);
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);
        root = newRoot;
    }
    insertInternal(key, value, root, nullptr);
}

template <typename Key, typename Value>
void BPlusTree<Key, Value>::remove(const Key& key) {
    removeInternal(key, root);
    if (!root->isLeaf && root->keys.empty()) {
        root = root->children[0];
    }
}

template <typename Key, typename Value>
void BPlusTree<Key, Value>::removeInternal(const Key& key, std::shared_ptr<BPlusTreeNode<Key, Value>> node) {
    auto it = std::lower_bound(node->keys.begin(), node->keys.end(), key);
    int index = it - node->keys.begin();

    if (node->isLeaf) {
        if (it != node->keys.end() && *it == key) {
            node->keys.erase(it);
            node->values.erase(node->values.begin() + index);
        }
    } else {
        if (it != node->keys.end() && *it == key) {
            if (node->children[index]->keys.size() >= degree) {
                auto predNode = node->children[index];
                while (!predNode->isLeaf) {
                    predNode = predNode->children.back();
                }
                Key predKey = predNode->keys.back();
                Value predValue = predNode->values.back();
                removeInternal(predKey, node->children[index]);
                node->keys[index] = predKey;
                node->values[index] = predValue;
            } else if (node->children[index + 1]->keys.size() >= degree) {
                auto succNode = node->children[index + 1];
                while (!succNode->isLeaf) {
                    succNode = succNode->children.front();
                }
                Key succKey = succNode->keys.front();
                Value succValue = succNode->values.front();
                removeInternal(succKey, node->children[index + 1]);
                node->keys[index] = succKey;
                node->values[index] = succValue;
            } else {
                mergeChild(node, index);
                removeInternal(key, node->children[index]);
            }
        } else {
            if (node->children[index]->keys.size() < degree) {
                if (index > 0 && node->children[index - 1]->keys.size() >= degree) {
                    auto leftSibling = node->children[index - 1];
                    auto child = node->children[index];
                    child->keys.insert(child->keys.begin(), node->keys[index - 1]);
                    child->values.insert(child->values.begin(), node->values[index - 1]);
                    if (!leftSibling->isLeaf) {
                        child->children.insert(child->children.begin(), leftSibling->children.back());
                        leftSibling->children.pop_back();
                    }
                    node->keys[index - 1] = leftSibling->keys.back();
                    node->values[index - 1] = leftSibling->values.back();
                    leftSibling->keys.pop_back();
                    leftSibling->values.pop_back();
                } else if (index < node->keys.size() && node->children[index + 1]->keys.size() >= degree) {
                    auto rightSibling = node->children[index + 1];
                    auto child = node->children[index];
                    child->keys.push_back(node->keys[index]);
                    child->values.push_back(node->values[index]);
                    if (!rightSibling->isLeaf) {
                        child->children.push_back(rightSibling->children.front());
                        rightSibling->children.erase(rightSibling->children.begin());
                    }
                    node->keys[index] = rightSibling->keys.front();
                    node->values[index] = rightSibling->values.front();
                    rightSibling->keys.erase(rightSibling->keys.begin());
                    rightSibling->values.erase(rightSibling->values.begin());
                } else {
                    if (index < node->keys.size()) {
                        mergeChild(node, index);
                    } else {
                        mergeChild(node, index - 1);
                    }
                }
            }
            removeInternal(key, node->children[index]);
        }
    }
}

template <typename Key, typename Value>
void BPlusTree<Key, Value>::splitChild(std::shared_ptr<BPlusTreeNode<Key, Value>> node, int index) {
    auto child = node->children[index];
    auto newChild = std::make_shared<BPlusTreeNode<Key, Value>>(child->isLeaf);
    node->keys.insert(node->keys.begin() + index, child->keys[degree - 1]);
    node->children.insert(node->children.begin() + index + 1, newChild);

    newChild->keys.assign(child->keys.begin() + degree, child->keys.end());
    child->keys.resize(degree - 1);

    if (!child->isLeaf) {
        newChild->children.assign(child->children.begin() + degree, child->children.end());
        child->children.resize(degree);
    } else {
        newChild->values.assign(child->values.begin() + degree, child->values.end());
        child->values.resize(degree - 1);
        newChild->next = child->next;
        child->next = newChild;
    }
}

template <typename Key, typename Value>
void BPlusTree<Key, Value>::mergeChild(std::shared_ptr<BPlusTreeNode<Key, Value>> node, int index) {
    auto leftChild = node->children[index];
    auto rightChild = node->children[index + 1];

    leftChild->keys.push_back(node->keys[index]);
    leftChild->keys.insert(leftChild->keys.end(), rightChild->keys.begin(), rightChild->keys.end());

    if (!leftChild->isLeaf) {
        leftChild->children.insert(leftChild->children.end(), rightChild->children.begin(), rightChild->children.end());
    } else {
        leftChild->values.insert(leftChild->values.end(), rightChild->values.begin(), rightChild->values.end());
        leftChild->next = rightChild->next;
    }

    node->keys.erase(node->keys.begin() + index);
    node->children.erase(node->children.begin() + index + 1);
}

template <typename Key, typename Value>
bool BPlusTree<Key, Value>::searchInternal(const Key& key, Value& value, std::shared_ptr<BPlusTreeNode<Key, Value>> node) const {
    auto it = std::lower_bound(node->keys.begin(), node->keys.end(), key);
    int index = it - node->keys.begin();
    if (node->isLeaf) {
        if (it != node->keys.end() && *it == key) {
            value = node->values[index];
            return true;
        }
        return false;
    } else {
        return searchInternal(key, value, node->children[index]);
    }
}

template class BPlusTree<int, int>; // Explicit instantiation for int key and value